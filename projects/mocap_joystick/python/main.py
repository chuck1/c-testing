import numpy as np
from scipy.optimize import fsolve

def normalize(v):
    return v / np.linalg.norm(v)

class Line:
    def __init__(self):
        self.p1 = np.array([[0],[0],[0]])
        self.p2 = np.array([[0],[0],[0]])

class Ray:
    def __init__(self, p, d):
        self.p = p #np.array([[0],[0],[0]])
        self.d = d #np.array([[0],[0],[0]])

    def at(self, f):
        return self.p + self.d * f;

def closest(r1, r2):
    w0 = r1.p - r2.p

    #print r1.d
    #print r2.d
    
    r1d = np.reshape(r1.d,3)
    r2d = np.reshape(r2.d,3)

    a = np.dot(r1d, r1d)
    b = np.dot(r1d, r2d)
    c = np.dot(r2d, r2d)
    d = np.dot(r1d, w0)
    e = np.dot(r2d, w0)

    sc = (b*e - c*d)/(a*c - b*b)
    tc = (a*e - b*d)/(a*c - b*b)
	
    l = Line()
    l.p1 = r1.at(sc)
    l.p2 = r2.at(tc)

    return l;

class Camera:
    def __init__(self, o, x, y, z):
        self.o = o
        self.x = normalize(x)
        self.y = normalize(y)
        self.z = normalize(z)
        self.S = np.concatenate((x,y),axis=1)
        #print self.S

    def get_ray(self, s):
        s = np.array(s)
        #print self.S
        #print s

        #xy = self.S * s
        xy = np.dot(self.S, s)

        #print xy
        return Ray(self.o, -self.z + xy)

    def get_screen(self, p):
        #print "get_screen"
        
        d = p - self.o
        
        dz = np.dot(d.T,self.z)[0][0]
        if dz == 0.0:
            print "p",p
            print "d",d
            print "o",self.o
            print dz
            raise BaseException()
        
        
        def func(X):
            #print "X",X
            k = X[0]
            s = np.array([X[1:]]).T
            #print k
            #print s
            
            d = -self.z + np.dot(self.S, s)   
           
            #print "d",d

            e = self.o + k * d - p

            #print "e",e

            return np.reshape(e, 3)


        X = fsolve(func, [[1],[0],[0]])

        s = np.array([X[1:]]).T

        return s

"""
struct Pose
{
	glm::vec3	p;
	glm::quat	q;
};
struct Frame
{
	// this frame is composed of three points fixed relative to each other
	// one point is defined as at the frame's origin
	// one is defined as along the -z axis
	// the relative position of the other is stored in the 'p' data member
	
	// get global pose of the frame based on the global position of the three points
	Pose		get_pose(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{

		Pose pose;

		return pose;
	}
	glm::vec3	p;
};


"""

class Mocap:
    def __init__(self):
        self.cam1 = Camera(
                np.array([[ 0, 0, 2]]).T,
                np.array([[ 1, 0, 0]]).T,
                np.array([[ 0, 1, 0]]).T,
                np.array([[ 0, 0, 1]]).T,
                )
        self.cam2 = Camera(
                np.array([[ 0, 2, 0]]).T,
                np.array([[ 0, 0,-1]]).T,
                np.array([[-1, 0, 0]]).T,
                np.array([[ 0, 1, 0]]).T,
                )

    def calibrate(self, s0, s1):
        print "calibrate"

        o_2_guess = np.array([[ 0.1, 2  , 0]]).T
        x_2_guess = np.array([[ 0  , 0.1,-1]]).T
        y_2_guess = np.array([[-1.1, 0  , 0]]).T
        #_2_guess = np.array([[ 0, 1, 0]]).T

        # (9,1)
        X_guess = np.concatenate((o_2_guess, x_2_guess, y_2_guess))
    
        #print X_guess

        # function which should equal zero
        def func(X):
            #print np.shape(X)
            o_2 = np.array([X[0:3]]).T
            x_2 = np.array([X[3:6]]).T
            y_2 = np.array([X[6:9]]).T
            #print o_2
            #print x_2
            #print y_2
            
            z_2 = np.reshape(np.cross(np.reshape(x_2,3), np.reshape(y_2,3)),(3,1))
               
            #print z_2
    
            cam2 = Camera(o_2, x_2, y_2, z_2)

            d = np.zeros(9)

            for i in range(9):
    
                r1 = self.cam1.get_ray(s0[i])
                r2 = cam2.get_ray(s1[i])
                
                l = closest(r1,r2)
                
                #print "line"
                #print l.p1
                #print l.p2
    
                d12 = l.p2 - l.p1

                d[i] = np.dot(d12.T,d12)[0][0]
            
            #print d

            return d

        X = fsolve(func, X_guess)

        o_2 = np.array([X[0:3]]).T
        x_2 = np.array([X[3:6]]).T
        y_2 = np.array([X[6:9]]).T
        z_2 = np.reshape(np.cross(np.reshape(x_2,3), np.reshape(y_2,3)),(3,1))
        cam2 = Camera(o_2, x_2, y_2, z_2)
        
        print "o_2"
        print cam2.o
        print "x_2"
        print cam2.x
        print "y_2"
        print cam2.y
        print "z_2"
        print cam2.z

        pass

    def get_position(self, s1, s2):
        r1 = self.cam1.get_ray(s1)
        r2 = self.cam2.get_ray(s2)
	
        l = closest(r1, r2)

        return l

    def get_screen(self, p):
        #print "get_screen"

        return self.cam1.get_screen(p), self.cam2.get_screen(p)

m = Mocap()

l = m.get_position(
        [[0],[0]],
        [[0],[0]])

#print l.p1
#print l.p2

# test points
points = [
        [[0  ],[0],[0]],
        [[1  ],[0],[0]],
        [[0  ],[1],[0]],
        [[0  ],[0],[1]],
        [[1  ],[1],[0]],
        [[0  ],[1],[1]],
        [[1  ],[0],[1]],
        [[1  ],[1],[1]],
        [[0.2],[1],[0]],
        ]

s0 = np.zeros((9,2,1))
s1 = np.zeros((9,2,1))

for i in range(9):
    p = points[i]
    print p
    s0[i], s1[i] = m.get_screen(p)
    #print s[i,0]
    #print s[i,1]


m.calibrate(s0, s1)

