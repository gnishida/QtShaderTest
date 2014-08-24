#version 150

in vec3 varColor;
in vec3 varNormal;
out vec4 gl_FragColor;
 
uniform vec3 lightDir;

void main()
{
	vec4 ambientIllumination = vec4(0.1,0.1,0.1,0.1);
	vec4 diffuseIllumination = vec4(1.0,1.0,1.0,1.0) * max(0.0, dot(-lightDir, varNormal));

	gl_FragColor = (ambientIllumination + diffuseIllumination) * vec4(varColor, 1.0);
}

