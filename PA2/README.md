# PA2 Mandelbrot

# REPORT IS UNDER PA2/PA2Report.pdf
# Dependencies, Building, and Running

## Dependency Instructions
These projects depend on the MPI Library and SLIURM Running environment preinstalled in [h1.cse.unr.edu](h1.cse.unr.edu).  There are no instructions included on how to install these suites on your personal machines.
If you are using a Windows machine, you may SSH into your respective UNR accounts through [PuTTY] (http://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).

You may enter h1 off campus by first logging into your account through ubuntu.cse.unr.edu.  (Please note that keystrokes will be a tiny bit slower, but it's still manageable).
```bash
ssh username@ubuntu.cse.unr.edu
ssh username@h1.cse.unr.edu
```

# Sequential Code 
Below is what the code will look like for sequential
```bash
    for( int y = 0; y < display_height; y++ )
    {
        for( int x = 0; x < display_width; x++ )
            {
            c.real = real_min + ((float)x * scale_real);
            c.imag = imag_min + ((float)y * scale_imag);
            r[y][x] = 0;
            g[y][x] = 0;
            b[y][x] = cal_pixel(c);
            }
    }
```

# Dynamic Code 
Below is what the code will look like for sequential
```bash
 while( rowsAnalyzed < display_height ) 
            {
			MPI_Recv( &row_colors, display_width + 1, MPI_INT, MPI_ANY_SOURCE, RESULT_TAG, MPI_COMM_WORLD, &status );
            int pingPongSend = status.MPI_SOURCE;
			int receivedRow = row_colors[0];
				
			// set the row which has finished computing
			for( int col = 0; col < display_width; col++ ) 
                {
				coords[receivedRow][col] = row_colors[col+1];
				}
				
				// increment row to send the next one
			rowsAnalyzed++;
			if( row < display_height ) 
                {
				// now we can send more data to whichever slave just finished
				MPI_Send( &row, 1, MPI_INT, pingPongSend, DATA_TAG, MPI_COMM_WORLD );
				row++;
				}

			}
```

# Times
Times that are in recorded into a text file will look like they are below (Processor/box, Resolution x/y, time)
```bash
1	600	0.12511
1	700	0.166914
1	800	0.21516
1	900	0.276056
1	1000	0.339467
1	1100	0.409625
1	1200	0.486853
1	1300	0.569081
1	1400	0.660456
1	1500	0.760387
1	1600	0.859621
1	1700	0.972867
1	1800	1.091734
1	1900	1.216932
1	2000	1.344192
1	2100	1.483962
1	2200	1.625854
1	2300	1.775402
1	2400	1.935623
1	2500	2.098118
1	2600	2.270674
1	2700	2.448498
1	2800	2.632158
1	2900	2.824471
1	3000	3.022541
1	3100	3.227762
1	3200	3.439242
1	3300	3.654089
1	3400	3.882499
1	3500	4.115172
1	3600	4.353659
1	3700	4.5933
1	3800	4.849307
1	3900	5.103939
1	4000	5.373272
1	4100	5.646673
1	4200	5.925299
1	4300	6.210893
1	4400	6.503446
1	4500	8.06877
1	4600	8.394447
1	4700	8.742386
1	4800	9.089644
1	4900	9.442841
1	5000	9.803413
1	5100	10.160819
1	5200	10.544041
```

## Building and Running
You may simple run the build with a few commands.
```bash
(Make sure you are under CS415_Lewis/PA2)
mkdir build
cp makefile seqMan.sh dynAssMan.sh build/
cd build
make
sbatch seqMan.sh
sbatch dynAssMan.sh
make clean
```
# Your results will be in shortly ;)
