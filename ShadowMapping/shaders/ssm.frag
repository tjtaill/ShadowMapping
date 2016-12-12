uniform sampler2DShadow ShadowMap;
uniform float Epsilon;
uniform float ShadowRatio;

varying vec4 ShadowCoord;

float lookup()
{
  float depth = 
    shadow2DProj( ShadowMap, ShadowCoord).r;

  return depth != 1.0 ? ShadowRatio : 1.0;
}

void main()
{
  float shadeFactor = lookup();

  gl_FragColor = vec4( shadeFactor * gl_Color.rgb, gl_Color.a );

}
