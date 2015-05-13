#version 330 core

struct light
{
	vec3 position;
	vec4 diffuse;
};
struct ray
{
	vec3 origin;
	vec3 direction;
};
struct sphere
{
	vec3 center;
	float radius;
	vec4 color;
};
struct plane
{
	vec3 n;
	float d;
	vec4 color;
};

/*
uniform SPHERES
{
	sphere S[128];
};
uniform PLANES
{
	plane P[128];
	};
 */
sphere S[8];
plane P[8];
light lights[8];


//uniform int num_spheres;
//uniform int num_planes;

int num_spheres = 2;
int num_planes = 2;

uniform vec2 screen;

int num_trace = 20;

float intersect_ray_plane(ray R, plane P, out vec3 hitpos, out vec3 normal)
{
	vec3 O = R.origin;
	vec3 D = R.direction;
	vec3 N = P.n;
	float d = P.d;

	float denom = dot(N,D);

	if(denom == 0.0) return 0.0;

	float t = -(d + dot(O,N)) / denom;

	if(t < 0.0) return 0.0;

	hitpos = O + t * D;
	normal = N;

	return t;
}
float intersect_ray_sphere(ray R, sphere S, out vec3 hitpos, out vec3 normal)
{
	vec3 v = R.origin - S.center;
	float B = 2.0 * dot(R.direction, v);
	float C = dot(v,v) - S.radius * S.radius;
	float B2 = B * B;

	float f = B2 - 4.0 * C;

	if(f < 0.0) return 0.0;

	float t0 = -B + sqrt(f);
	float t1 = -B - sqrt(f);
	float t = min(max(t0, 0.0), max(t1, 0.0)) * 0.5;

	if(t == 0.0) return 0.0;

	hitpos = R.origin + t * R.direction;
	normal = normalize(hitpos - S.center);

	return t;
}


// using alpha as reflectivity, no transparency at this point


int search(inout ray R, out vec3 hit_normal, out int index)
{
	int object_type = -1;

	float min_t = 100000000.0f;
	float t;

	vec3 normal;
	vec3 hitpos;
	vec3 hit_position;
	vec3 hit_direction;

	for(int i = 0; i < num_spheres; ++i)
	{
		// find intersection point
		t = intersect_ray_sphere(R, S[i], hitpos, normal);

		// if there is an intersection
		if(t != 0.0)
		{
			// and that intersection is less than out current closest
			if(t < min_t)
			{
				// record it
				min_t = t;
				hit_position = hitpos;
				hit_normal = normal;
				index = i;
				object_type = 0;
			}
		}
	}

	for(int i = 0; i < num_planes; ++i)
	{
		// find intersection point
		t = intersect_ray_plane(R, P[i], hitpos, normal);

		// if there is an intersection
		if(t != 0.0)
		{
			// and that intersection is less than out current closest
			if(t < min_t)
			{
				// record it
				min_t = t;
				hit_position = hitpos;
				hit_normal = normal;
				index = i;
				object_type = 1;
			}
		}
	}

	R.origin = hit_position;
	R.direction = reflect(R.direction, hit_normal);
	R.direction = normalize(R.direction);

	return object_type;
}

vec4 trace(ray R)
{
	//ret_color = vec4(0.0);
	ray newR;

	vec3 normal;

	int object_type;
	int index;
	
	float a = 1.0;
	
	vec4 o = vec4(0.0,0.0,0.0,1.0);

	for(int j = 0; j < num_trace; ++j)
	{
		object_type = search(R, normal, index);

		// return if ray didnt intersect anything
		if(object_type == -1) break;

		// get color for object hit by this ray
		vec4 c = vec4(0.0,0.0,0.0,0.0);
		if(object_type == 0)
		{
			c = S[index].color;
		}
		else if(object_type == 1)
		{
			c = P[index].color;
		}
		else break;
		
		// apply lighting to color
		vec3 L = lights[0].position - R.origin;
		c = c * lights[0].diffuse * max(dot(L,normal),0);


		// blend with color returned by fired ray
		o.rgb += c.rgb * c.a * a;
		
		a *= (1.0 - c.a);
		
		if(a == 0.0) break;

	}

	return o;
}



// texture with ray origin and direction
//uniform sampler2D tex_origin;
//uniform sampler2D tex_direction;


out vec4 color;

void main(void)
{
	S[0].center = vec3(-1.0,-0.5,-3.0);
	S[0].radius = 0.5;
	S[0].color = vec4(0.0,1.0,1.0,1.0);

	S[1].center = vec3(1.0,0.5,-3.0);
	S[1].radius = 0.5;
	S[1].color = vec4(1.0,0.0,1.0,1.0);

	P[0].n = vec3(0.0,0.0,-1.0);
	P[0].d = 1.0;
	P[0].color = vec4(0.0,0.5,0.0,0.0);

	P[1].n = vec3(0.0,0.0,1.0);
	P[1].d = 6.0;
	P[1].color = vec4(0.0,0.5,0.0,0.0);



	lights[0].position = vec3(0.0,0.0,-3.0);
	lights[0].diffuse = vec4(1.0,1.0,1.0,1.0);

	ray R;

	//R.origin = texelFetch(tex_origin, ivec2(gl_FragCoord.xy), 0).xyz;
	//R.direction = texelFetch(tex_direction, ivec2(gl_FragCoord.xy), 0).xyz;

	vec2 p;
	p.x = gl_FragCoord.x / screen.x;
	p.y = gl_FragCoord.y / screen.y;

	p -= vec2(0.5,0.5);


	R.origin = vec3(0.0,0.0,0.0);
	R.direction = vec3(p,-1.0);
	R.direction = normalize(R.direction);

	color = trace(R);
	//recurse(R, color, 1);

	//color = vec4(1.0,1.0,0.0,1.0);
	//color.rg = abs(R.direction).xy;
}



