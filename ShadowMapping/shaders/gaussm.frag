#define KERNEL_SIZE 9
uniform sampler2DShadow ShadowMap;
uniform float Epsilon;
uniform float ShadowRatio;

varying vec4 ShadowCoord;

float lookup(in vec2 offset)
{
  float depth = 
    shadow2DProj( ShadowMap, ShadowCoord + vec4(offset, 0, 0) ).r;

  return depth != 1.0 ? ShadowRatio : 1.0;
}

// Gaussian kernel
// 1 2 1
// 2 4 2
// 1 2 1	
float kernel[KERNEL_SIZE];

vec2 offset[KERNEL_SIZE];
						 
void main(void)
{
   int i = 0;
   float sum = 0.0;
   
   offset[0] = vec2(-Epsilon, -Epsilon);
   offset[1] = vec2(0.0, -Epsilon);
   offset[2] = vec2(Epsilon, -Epsilon);
   
   offset[3] = vec2(-Epsilon, 0.0);
   offset[4] = vec2(0.0, 0.0);
   offset[5] = vec2(Epsilon, 0.0);
   
   offset[6] = vec2(-Epsilon, Epsilon);
   offset[7] = vec2(0.0, Epsilon);
   offset[8] = vec2(Epsilon, Epsilon);
   
   kernel[0] = 1.0/16.0; 	kernel[1] = 2.0/16.0;	kernel[2] = 1.0/16.0;
   kernel[3] = 2.0/16.0;	kernel[4] = 4.0/16.0;	kernel[5] = 2.0/16.0;
   kernel[6] = 1.0/16.0;   	kernel[7] = 2.0/16.0;	kernel[8] = 1.0/16.0;
   
   /*
   for( i=0; i<KERNEL_SIZE; i++ )
   {
     sum += lookup( offset[i] ) * kernel[i];
   }
   */

 
   sum += lookup( offset[0] ) * kernel[0];
   sum += lookup( offset[1] ) * kernel[1]; 
   sum += lookup( offset[2] ) * kernel[2]; 
   sum += lookup( offset[3] ) * kernel[3]; 
   sum += lookup( offset[4] ) * kernel[4]; 
   sum += lookup( offset[5] ) * kernel[5]; 
   sum += lookup( offset[6] ) * kernel[6];
   sum += lookup( offset[7] ) * kernel[7];
   sum += lookup( offset[8] ) * kernel[8];

   gl_FragColor = vec4(sum * gl_Color.rgb, gl_Color.a);
}
