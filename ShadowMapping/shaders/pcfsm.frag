uniform sampler2DShadow ShadowMap;
uniform float Epsilon;
uniform float ShadowRatio;

varying vec4 ShadowCoord;

float lookup(in float s, in float t)
{
  float depth = 
    shadow2DProj( ShadowMap, ShadowCoord + vec4(s, t, 0, 0) * Epsilon ).r;

  return depth != 1.0 ? ShadowRatio : 1.0;
}

void main()
{
  float sum = 0.0;

  sum += lookup( -0.5, -0.5 );
  sum += lookup(  0.5, -0.5 );
  sum += lookup( -0.5,  0.5 );
  sum += lookup(  0.5,  0.5 );

  gl_FragColor = vec4( sum * 0.25 * gl_Color.rgb, gl_Color.a );

}
