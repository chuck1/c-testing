#include "body.hpp"
#include "ellipse.hpp"

ellipse::ellipse(plane p, float a, float b, float e):
	conic(p, a, e),
	b_(b)
{
	assert(a_ > b_);

	c_ = sqrt(a_*a_ - b_*b_);
	per_ = a_ - c_;

	p_ = a_ * (1 - pow(e,2));

}
void		ellipse::standard_line() {
	generate_line(0, TAU);
}
void		ellipse::draw(float time, glm::vec3 center) {
	//cout << "draw ellipse" << endl;
	glColor3fv(colorWhite);
	if(line_.empty()) {
		standard_line();
	}
	
	glm::vec3 x = b2_->x(time) - center;
	
	glPushMatrix();
	glTranslatef(x[0], x[1], x[2]);
	line_loop(line_);
	glPopMatrix();

}
float		ellipse::x(float t) {
	return a_ * cos(t) + c_;
}
float		ellipse::y(float t) {
	return b_ * sin(t);
}
glm::vec3	ellipse::X(float time) {

	float ta = true_anomaly_from_time(time);

	float r = p_ / (1.0 + e_ * cos(ta));

	glm::vec3 R = glm::rotate(plane_.x_, ta, plane_.n_) * r + plane_.c_;

	return R;
}
glm::vec3	ellipse::V(float time) {

	float ta = true_anomaly_from_time(time);

	float aov = atan(e_ * sin(ta) / (1.0 + e_ * cos(ta)));

	//float tmp = (mu_/p_)*(1.0 + pow(e_,2) - 2.0 * cos(ta));

	float r = p_ / (1.0 + e_ * cos(ta));

	float tmp = mu_ * (2.0 / r - 1.0 / a_);

	float v = sqrt(tmp);

	glm::vec3 V =  glm::rotate(plane_.x_, (float)(ta + TAU / 4.0 + aov), plane_.n_) * v;

	/*		cout << "(mu_/p_) = " << (mu_/p_) << endl;
			cout << "cos(ta) = " << cos(ta) << endl;
			cout << "tmp = " << tmp << endl;
			cout << "ta = " << ta << endl;
			cout << "aov = " << aov << endl;
			cout << "v = " << v << endl;
			cout << "mu = " << mu_ << endl;
			cout << "p = " << p_ << endl;
			cout << "e = " << e_ << endl;
			*/
	assert(!glm::any(glm::isnan(V)));

	return V;
}

 float		ellipse::time_from_periapsis(float time) {
	float tfp = time - epoch_;
	while(tfp > period()) tfp -= period();
	return tfp;
}
 float		ellipse::mean_anomaly_from_time_from_periapsis(float time_from_periapsis) {
	return (time_from_periapsis * TAU) / period();
}
 float		ellipse::period() {
	return TAU *pow(pow(a_, 3) / mu_, 0.5);
}
 float		ellipse::mean_anomaly_from_eccentric_anomaly(float E) {
	return E - e_ * sin(E);
}
 float		ellipse::eccentric_anomaly_from_mean_anomaly(float M) {
	float E = M + e_ * sin(M);
	E = M + e_ * sin(E);
	E = M + e_ * sin(E);
	return E;
}
 float		ellipse::true_anomaly_from_eccentric_anomaly(float E) {
	return atan2(sqrt(1+e_) * sin(E/2.0), sqrt(1-e_) * cos(E/2.0));
}
 float		ellipse::true_anomaly_from_time(float time) {
	float M = mean_anomaly_from_time_from_periapsis(time_from_periapsis(time));
	float E = eccentric_anomaly_from_mean_anomaly(M);
	float true_anomaly = true_anomaly_from_eccentric_anomaly(E);
	return true_anomaly;
}

