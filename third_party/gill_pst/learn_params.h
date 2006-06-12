
#ifndef _learn_params_h
#define _learn_params_h

/* learning parameters */

/* alg 1 */

double p_min;
double alpha;
double gamma_min = 1; /* so un-inited runs of alg1 will fail */
double p_ratio;
int L_max;

/* alg 2 */

/* p_ratio, L_max */
double shows;
double gama; /* correct spelling coincides with a math lib var*/
double mue = 5;  /* alg-2 smoothing factor */
double p0[] = {  /* DEFUNCT */
                /* A */ 7.544e-02,
                /* B */ 2.164e-05,
	        /* C */ 1.701e-02,
	        /* D */ 5.297e-02,
	        /* E */ 6.316e-02,
	        /* F */ 4.067e-02,
	        /* G */ 6.861e-02,
	        /* H */ 2.232e-02,
	        /* I */ 5.726e-02,
	        /* K */ 5.950e-02,
	        /* L */ 9.317e-02,
	        /* M */ 2.362e-02,
	        /* N */ 4.545e-02,
	        /* P */ 4.917e-02,
	        /* Q */ 4.030e-02,
	        /* R */ 5.156e-02,
	        /* S */ 7.193e-02,
	        /* T */ 5.764e-02,
	        /* V */ 6.522e-02,
	        /* W */ 1.262e-02,
	        /* X */ 2.153e-04,
	        /* Y */ 3.212e-02,
	        /* Z */ 2.072e-05
              };

	   
double Q[23]; /* inited inside alg2's smoother */

const double q[23][23] =
{ /* -------------------------------------------------------------- */

{26782.81,    10.00,  3962.65,  5400.73,  7444.98,  4076.59, 14491.39,  2759.96,  7943.72,  8338.88, 11009.91,  3341.90,  4857.14,  5374.35,  4794.70,  5848.09, 15579.38,  9264.29, 12627.73,  1003.70,    10.00,  3239.21,    10.00},
{   10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00},
{ 3962.65,    10.00, 14864.71,   994.42,   955.29,  1280.49,  1917.42,   572.50,  2730.06,  1248.97,  3907.74,   939.80,  1092.50,   899.80,   770.86,   980.88,  2599.50,  2318.32,  3390.37,   360.67,    10.00,   862.22,    10.00},
{ 5400.73,    10.00,   994.42, 26504.98, 12248.73,  1894.29,  6284.36,  2376.71,  3076.61,  6092.99,  3787.90,  1156.88,  9269.63,  3083.07,  4106.64,  3953.21,  6985.53,  4724.65,  3278.68,   404.11,    10.00,  1491.09,    10.00},
{ 7444.98,    10.00,   955.29, 12248.73, 20100.50,  2122.42,  4829.16,  3405.63,  3037.90, 10296.37,  4990.96,  1692.11,  5505.96,  3542.26,  8817.09,  6711.13,  7360.29,  5106.27,  4232.85,   660.02,    10.00,  2168.88,    10.00},
{ 4076.59,    10.00,  1280.49,  1894.29,  2122.42, 22771.30,  2984.24,  2019.30,  7589.45,  2364.01, 13492.91,  2965.57,  1868.88,  1308.84,  1351.88,  2321.82,  2975.00,  2896.40,  6419.39,  2115.89,    10.00, 10562.84,    10.00},
{14491.39,    10.00,  1917.42,  6284.36,  4829.16,  2984.24, 47098.64,  2387.39,  3450.79,  6327.07,  5198.87,  1825.96,  7124.25,  3398.98,  3409.41,  4291.00,  9553.90,  5446.48,  4539.45,  1015.14,    10.00,  2079.76,    10.00},
{ 2759.96,    10.00,   572.50,  2376.71,  3405.63,  2019.30,  2387.39, 11561.82,  1447.42,  2958.56,  2459.23,   953.44,  3563.41,  1190.29,  2613.56,  3091.55,  2753.84,  1853.12,  1616.69,   377.94,    10.00,  3790.82,    10.00},
{ 7943.72,    10.00,  2730.06,  3076.61,  3037.90,  7589.45,  3450.79,  1447.42, 22975.42,  3900.98, 28361.76,  6249.52,  2477.68,  2508.69,  2220.18,  3098.65,  4291.98,  6716.05, 29832.35,   901.59,    10.00,  3443.82,    10.00},
{ 8338.88,    10.00,  1248.97,  6092.99, 10296.37,  2364.01,  6327.07,  2958.56,  3900.98, 20074.90,  6138.15,  2264.38,  6080.29,  3930.17,  7716.37, 15533.06,  7728.29,  5847.29,  4824.05,   677.71,    10.00,  2489.43,    10.00},
{11009.91,    10.00,  3907.74,  3787.90,  4990.96, 13492.91,  5198.87,  2459.23, 28361.76,  6138.15, 46272.78, 12282.50,  3411.38,  3524.79,  4030.19,  6028.42,  6049.14,  8281.94, 23617.94,  1824.09,    10.00,  5505.85,    10.00},
{ 3341.90,    10.00,   939.80,  1156.88,  1692.11,  2965.57,  1825.96,   953.44,  6249.52,  2264.38, 12282.50,  5042.88,  1319.20,  1017.22,  1843.69,  2001.08,  2132.99,  2515.49,  5761.66,   495.17,    10.00,  1423.89,    10.00},
{ 4857.14,    10.00,  1092.50,  9269.63,  5505.96,  1868.88,  7124.25,  3563.41,  2477.68,  6080.29,  3411.38,  1319.20, 17616.72,  2143.28,  3813.41,  4930.09,  7840.40,  5571.65,  2993.54,   402.65,    10.00,  1745.40,    10.00},
{ 5374.35,    10.00,   899.80,  3083.07,  3542.26,  1308.84,  3398.98,  1190.29,  2508.69,  3930.17,  3524.79,  1017.22,  2143.28, 23753.47,  2109.68,  2386.63,  4151.82,  3366.54,  3102.50,   352.63,    10.00,  1126.86,    10.00},
{ 4794.70,    10.00,   770.86,  4106.64,  8817.09,  1351.88,  3409.41,  2613.56,  2220.18,  7716.37,  4030.19,  1843.69,  3813.41,  2109.68,  9131.13,  6194.03,  4717.08,  3437.77,  2905.57,   566.56,    10.00,  1684.00,    10.00},
{ 5848.09,    10.00,   980.88,  3953.21,  6711.13,  2321.82,  4291.00,  3091.55,  3098.65, 15533.06,  6028.42,  2001.08,  4930.09,  2386.63,  6194.03, 22123.18,  5646.43,  4435.93,  3939.43,   662.10,    10.00,  2308.18,    10.00},
{15579.38,    10.00,  2599.50,  6985.53,  7360.29,  2975.00,  9553.90,  2753.84,  4291.98,  7728.29,  6049.14,  2132.99,  7840.40,  4151.82,  4717.08,  5646.43, 15680.23, 11712.22,  5877.26,   715.91,    10.00,  2566.42,    10.00},
{ 9264.29,    10.00,  2318.32,  4724.65,  5106.27,  2896.40,  5446.48,  1853.12,  6716.05,  5847.29,  8281.94,  2515.49,  5571.65,  3366.54,  3437.77,  4435.93, 11712.22, 15591.62,  9070.39,   712.02,    10.00,  2346.22,    10.00},
{12627.73,    10.00,  3390.37,  3278.68,  4232.85,  6419.39,  4539.45,  1616.69, 29832.35,  4824.05, 23617.94,  5761.66,  2993.54,  3102.50,  2905.57,  3939.43,  5877.26,  9070.39, 24458.47,   886.51,    10.00,  3859.61,    10.00},
{ 1003.70,    10.00,   360.67,   404.11,   660.02,  2115.89,  1015.14,   377.94,   901.59,   677.71,  1824.09,   495.17,   402.65,   352.63,   566.56,   662.10,   715.91,   712.02,   886.51,  8060.58,    10.00,  2211.24,    10.00},
{   10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00},
{ 3239.21,    10.00,   862.22,  1491.09,  2168.88, 10562.84,  2079.76,  3790.82,  3443.82,  2489.43,  5505.85,  1423.89,  1745.40,  1126.86,  1684.00,  2308.18,  2566.42,  2346.22,  3859.61,  2211.24,    10.00, 12765.13,    10.00},
{   10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00,    10.00}

  /* -------------------------------------------------------------- */ };


/* these belong to the old smoother of alg 2
double beta;
double chi0;
*/




#endif /*_learn_params_h */
