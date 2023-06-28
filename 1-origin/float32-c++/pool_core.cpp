#include "pool_core.h"

void Pool(ap_uint<16> CHin,ap_uint<16> Hin,ap_uint<16> Win,
		ap_uint<8> Kx,ap_uint<8> Ky,ap_uint<2> mode,
		float  feature_in[],float  feature_out[]
	)
{
	#pragma HLS INTERFACE m_axi depth=4294967295 port=feature_out offset=slave
	#pragma HLS INTERFACE m_axi depth=4294967295 port=feature_in offset=slave
	#pragma HLS INTERFACE s_axilite port=Win
	#pragma HLS INTERFACE s_axilite port=Kx
	#pragma HLS INTERFACE s_axilite port=Hin
	#pragma HLS INTERFACE s_axilite port=mode
	#pragma HLS INTERFACE s_axilite port=Ky
	#pragma HLS INTERFACE s_axilite port=CHin
	#pragma HLS INTERFACE s_axilite port=return

	ap_uint<16> Hout,Wout;
	Wout=Win/Kx;
	Hout=Hin/Ky;

	for(int c=0;c<CHin;c++)
	{
#pragma HLS LOOP_TRIPCOUNT min=6 max=16 avg=11
		for(int i=0;i<Hout;i++)
		{
#pragma HLS LOOP_TRIPCOUNT min=7 max=14 avg=10
			for(int j=0;j<Wout;j++)
			{
#pragma HLS LOOP_TRIPCOUNT min=7 max=14 avg=10
				Dtype_f sum = -99999999999999999;
				for(int ii=0;ii<Ky;ii++)
				{
#pragma HLS LOOP_TRIPCOUNT min=2 max=2 avg=2
					for(int jj=0;jj<Kx;jj++)
					{
// #pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=2 max=2 avg=2
						ap_int<16> h=i*Ky+ii;
						ap_int<16> w=j*Kx+jj;
						if(sum<feature_in[h*CHin*Win+w*CHin+c])
							sum=feature_in[h*CHin*Win+w*CHin+c];
					}
				}
				feature_out[i*Wout*CHin+j*CHin+c]=sum;
			}
		}
	}
}
