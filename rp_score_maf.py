#!/usr/bin/env python

"""
Score a set of alignments (MAF format) using a model

usage: %prog data score_matrix out [options]
   -m, --mapping=FILE: A mapping (alphabet reduction) to apply to each sequence (optional)
   -M, --model=MODEL:  Name of model to use
   -w, --window=N:     Size of window to scroll over sequence (default 100)
   -s, --shift=N:      Amount to shift window (deafult 5)
   -b, --low=N:        Truncate to this minimum score
   -e, --high=N:       Truncate to this maximum score
   -r, --reorder=0,2,1:Reorder the species in each block before scoring.
"""

from __future__ import division

import bx.align.maf
import sys
import traceback

from bx.cookbook import doc_optparse

from numpy import *

import rp.io 
import rp.mapping
import rp.models

def run( data_file, modname, model_file, out_file, mapping, window, shift, low, high, reorder ):

    # Read model
    model = rp.models.get( modname ).from_file( model_file )
    radix = model.get_radix()

    # Open maf file
    mafs = bx.align.maf.Reader( data_file )

    # Score each alignment
    for i, maf in enumerate( mafs ):
        if mapping:
            assert len( maf.components ) ** rp.mapping.DNA.get_out_size() < mapping.get_in_size()
        if reorder: components = [ maf.components[ i ] for i in reorder ]
        else: components = maf.components
        ints = rp.mapping.DNA.translate_list( [ c.text for c in components ] )
        if mapping: ints = mapping.translate( ints )
        score_windows( maf, ints, model, out_file, window, shift, low, high )

def score_windows( maf, string, model, out, window, shift, low, high ):
    if maf.text_size < window: return
    half_window = window // 2
    rc = maf.components[0] 
    text = rc.text
    # Position in genome coordinates
    abs_pos = rc.start 
    last_window_center_scored = -1
    chrom = rc.src
    if '.' in chrom: chrom = chrom.split('.')[1]
    # Score array
    scores = array( [ float("nan") ] * len( text ), dtype="f" )
    model.score_positions( string, scores )
    # Build cumulative sum of scores AND of number of good words per window (note: nan!=nan)
    goodwords = equal(scores,scores)
    putmask( scores, not_equal(scores,scores) , 0 )
    # Wiggle header 
    print >>out, "variableStep chrom=" + chrom
    #print >>out, "fixedStep chrom=%s start=%d step=%d" % ( chrom, abs_pos, shift )
    for i, c in enumerate( text ):
        if i + window >= len( text ): 
            break
        # Don't score windows that start with a gap
        if c == '-':
            continue
        abs_pos += 1
        # Determine number of reference gaps in window, if more than half, skip
        gaps_in_window = text.count( '-', i, i + window )
        if gaps_in_window > half_window:
            continue
        # Determine center of window in genome coordinates, if not increasing skip
        window_center = abs_pos + ( ( window - gaps_in_window ) // 2 )
        if window_center <= last_window_center_scored:
            continue
        if window_center % shift == 0:
            score = sum( scores[i:i+window] )
            ## score = model.score( string, i, window )
            ngood = sum( goodwords[i:i+window] )
            if ngood < 50: 
                continue
            ## print score, ngood
            score = score / ngood
            if score is not None:
                # if abs_pos == last_pos: continue
                if score > high: score = high
                elif score < low: score = low
                print >> out, window_center, round( score, 6 )
                ##   print >>out, round( score, 6 )
                last_window_center_scored = window_center

def getopt( options, name, default ):
    v = getattr( options, name )
    if v is None: return default
    return v

def main():

    # Parse command line
    options, args = doc_optparse.parse( __doc__ )
    try:
        data_fname, model_fname, out_fname = args
        window = int( getopt( options, 'window', 100 ) )
        shift = int( getopt( options, 'shift', 5 ) )
        low = float( getopt( options, 'low', -1.0 ) )
        high = float( getopt( options, 'high', 1.0 ) )
        if options.mapping:
            align_count, mapping = rp.mapping.alignment_mapping_from_file( file( options.mapping ) )
        else:
            mapping = None
        modname = getattr( options, 'model' )
        if modname is None: modname = 'standard'
        reorder = getopt( options, 'reorder', None )
        if reorder: reorder = map( int, reorder.split( ',' ) )
    except:
        doc_optparse.exception()

    out = open( out_fname, "w" )
    run( open( data_fname ), modname, open( model_fname ), out, mapping, window, shift, low, high, reorder )
    out.close()

if __name__ == "__main__": main()
