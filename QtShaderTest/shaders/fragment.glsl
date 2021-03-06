#version 330

// varying variables
in vec3 varColor;
in vec3 varTexCoord;
in vec3 varNormal;

// output color
out vec4 outputF;

// uniform variables
uniform int mode;	// 1 -- color / 2 -- texture
uniform sampler2D tex0;
uniform vec3 lightDir;

void main()
{
	// for color mode
	outputF = vec4(varColor, 1.0);

	if (mode == 2) { // for texture mode
		outputF = texture(tex0, varTexCoord.rg);
	}

	// lighting
	vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
	vec4 diffuse = vec4(0.8, 0.8, 0.8, 1.0) * max(0.0, dot(-lightDir, varNormal));

	outputF = (ambient + diffuse) * outputF;
}

