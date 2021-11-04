#include <iostream> 
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <math.h>
#include <ap_int.h>
#include <iostream>
#include <ap_axi_sdata.h>

using namespace std;

typedef ap_axis <32,2,5,6> int_side_ch;


unsigned int s1[2];
unsigned int d1[4];

  
void ack1(hls:: stream<int_side_ch> &inStream , hls:: stream<int_side_ch> &outStream,int gain)
{ 
#pragma HLS INTERFACE axis port=inStream
#pragma HLS INTERFACE axis port=outStream
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=gain bundle=CRTL_BUS

	int_side_ch val_in1;
	int_side_ch val_in2;
	int_side_ch val_out;
	val_in1= inStream.read();
	int x=(int)val_in1.data;
	val_in2= inStream.read();
	int y=(int)val_in2.data;

    //s1.push(m);
		int d1[4] = { 0,0,0,0 };
		int s1[2] = { 0,0 };
		int m1 = 0;
		int n1 = 0;
		int m = 0;
		int n = 0;
		//s1.push(m);


		s1[0] = x;

		s1[1] = y;

		n = x - 1;

		//while (!s1.empty()).
		while (d1[0] != 0 || d1[1] != 0 || d1[2] != 0 || d1[3] != 0 || s1[0] != 0)
		{

			m1 = s1[0];
			n1 = s1[1];
			if (m1 == 0) {
				if (d1[m] == 0 && d1[m - 1] != 0)
				{
					m = m - 1;
					n = x - 1 - m;
					d1[m] = d1[m] - 1;
					s1[0] = n;
					s1[1] = n1 + 1;
					m = m + 1;
					n = n - 1;
				}
				else if (d1[m] == 0 && d1[m - 1] == 0 && d1[m - 2] == 0)
				{
					m = m - 3;
					n = x - 1 - m;
					d1[m] = d1[m] - 1;
					s1[0] = n;
					s1[1] = n1 + 1;
					m = m + 1;
					n = n - 1;
				}
				else if (d1[m] == 0 && d1[m - 1] == 0)
				{
					m = m - 2;
					n = x - 1 - m;
					d1[m] = d1[m] - 1;
					s1[0] = n;
					s1[1] = n1 + 1;
					m = m + 1;
					n = n - 1;
				}

				else
				{
					s1[1] = s1[1] + 1;
					s1[0] = 0;
					d1[m]--;
				}
			}
			//s1.pop();
			else if (n1 == 0 && m1 == 1)
			{
				s1[1] = 1;
				s1[0] = 0;
			}
			else if (n1 == 0) {
				s1[1] = 1;
				s1[0] = m1 - 1;
				n = n - 1;
				m = m + 1;
			}
			else {

				s1[0] = m1;
				s1[1] = n1 - 1;
				d1[m]++;

			}

	    }
    val_out.data=s1[1]+1;
    outStream.write(val_out);
}

