#include "../Include/Vec3.h"
#include "../Include/Vec4.h"

int main() {
	float pi = 3.1415;


	Math::Vec4f yaw( Math::Vec3f(0,1,0), pi/2.0 );
	Math::Vec4f pitch( Math::Vec3f(1,0,0), pi/4.0 );

	Math::Vec4f rot(0,0,0,1);

	yaw.print();
	pitch.print();

	rot *= pitch;
	rot *= yaw;
	

	rot.print();

	Math::Vec3f v(0,1,0);

	

	v.print();

	v *= rot;

	v.print();

}



