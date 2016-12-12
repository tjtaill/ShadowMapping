uniform sampler2DShadow ShadowMap;
uniform float Epsilon;
uniform float ShadowRatio;

varying vec4 ShadowCoord;

float lookup(in vec2 offset)
{
  float depth = 
    shadow2DProj( ShadowMap, ShadowCoord + vec4(offset, 0, 0) * Epsilon ).r;

  return depth != 1.0 ? ShadowRatio : 1.0;
}

vec2 my_mod( in vec2 offset, in float number )
{
  return offset * floor( offset / number );
}

void main()
{
  float sum = 0.0;

  vec2 offset =  mod(floor(gl_FragCoord.xy), 2.0 );


  sum += lookup( vec2( -1.5, -1.5 ) + offset );
  sum += lookup( vec2(0.5,  1.5) + offset );
  sum += lookup( vec2(-1.5, -0.5) + offset );
  sum += lookup( vec2(0.5, -0.5) + offset );

  gl_FragColor = vec4( sum * 0.25 * gl_Color.rgb, gl_Color.a );

}
