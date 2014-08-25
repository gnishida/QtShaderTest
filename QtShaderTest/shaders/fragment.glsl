#version 330

// varying variables
in vec3 varColor;
in vec3 varTexCoord;
in vec3 varNormal;

out vec4 outputF;

// uniform variables
uniform int mode;
uniform sampler2D tex0;
uniform vec3 lightDir;

void main()
{
	outputF = vec4(varColor, 1.0);

	if (mode == 2) { // texture
		outputF = texture(tex0, varTexCoord.rg);
	}

	// lighting
	//vec3 normal = varNormal;
	vec4 ambient = vec4(0.2, 0.2, 0.2, 0.2);
	vec4 diffuse = vec4(0.8, 0.8, 0.8, 0.8) * max(0.0, dot(-lightDir, varNormal));

	outputF = (ambient + diffuse) * outputF;
}

