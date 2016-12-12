uniform int LightNumber;
uniform int TextureUnit;

varying vec4 ShadowCoord;

void PointLight( in int i,
		 in vec3 eye,
		 in vec3 ecPosition3,
		 in vec3 normal,
		 inout vec4 ambient,
		 inout vec4 diffuse,
		 inout vec4 specular )
{
  float nDotVP;
  float nDotHV;
  float pf;
  float attenuation;
  float d;
  vec3 VP;
  vec3 halfVector;

  VP = vec3( gl_LightSource[i].position ) - ecPosition3;

  d = length(VP);

  VP = normalize(VP);

  attenuation = 1.0 / ( gl_LightSource[i].constantAttenuation + 
			gl_LightSource[i].linearAttenuation * d +
			gl_LightSource[i].quadraticAttenuation * d * d);
  
  halfVector = normalize( VP + eye );

  nDotVP = max( 0.0, dot( normal, VP ));

  nDotHV = max( 0.0, dot( normal, halfVector ) );

  if ( nDotVP == 0.0 )
    pf = 0.0;
  else
    pf = pow( nDotHV, gl_FrontMaterial.shininess);

  ambient += gl_LightSource[i].ambient * attenuation;
  diffuse += gl_LightSource[i].diffuse * attenuation;
  specular += gl_LightSource[i].specular * pf * attenuation;

}


vec4 eye_coord( in vec4 ecPosition4, in int texture_unit )
{
  vec4 coord;
  coord.s = dot( ecPosition4, gl_EyePlaneS[texture_unit] );
  coord.t = dot( ecPosition4, gl_EyePlaneT[texture_unit] );
  coord.p = dot( ecPosition4, gl_EyePlaneR[texture_unit] );
  coord.q = dot( ecPosition4, gl_EyePlaneQ[texture_unit] );
  return coord;
}


void main()
{
  vec4 ecPosition4 = gl_ModelViewMatrix * gl_Vertex;
  vec3 ecPosition3 = vec3( ecPosition4 ) / ecPosition4.w;

  vec3 normal = normalize( gl_NormalMatrix * gl_Normal );

  vec3 eye = -normalize( ecPosition3 );

  vec4 ambient = vec4(0);
  vec4 diffuse = vec4(0);
  vec4 specular = vec4(0);

  PointLight( LightNumber, eye, ecPosition3, normal, ambient, diffuse, specular );

  vec4 color = gl_FrontLightModelProduct.sceneColor + 
    ambient * gl_FrontMaterial.ambient +
    diffuse * gl_FrontMaterial.diffuse +
    specular * gl_FrontMaterial.specular;

 
  ShadowCoord = gl_TextureMatrix[TextureUnit] * eye_coord( ecPosition4, TextureUnit );
  
  gl_FrontColor = color;
  
  gl_Position = ftransform();

}
