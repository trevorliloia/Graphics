#version 450
    layout(location = 0) in vec4 position;
    layout(location = 2) in vec2 texCoord;

	layout(location = 1) uniform int idx = 0;
    layout(location = 2) uniform int rows = 8;
	layout(location = 3) uniform int cols = 12;

    out vec2 vUV;
    void main ()
    { 

	int r = idx / cols;
	int c = idx % cols;
	gl_Position = position; 
	
	vUV = (vec2(r,c) + texCoord) / vec2(rows,cols);
	
	}

	//setUniforms(sq, loc, tslot, tex, 0, 4, 4)