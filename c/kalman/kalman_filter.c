void KalmanPosVel(void);
void initKalmanPosVel(void);

struct quad_properties{
	// State variables
	float height;
	float kalmanvel_z;
	float ;

	// Measurements
	float baro_height;
	float measured_az;
};

struct quad_properties quadprops;

struct matrix2x2{
	float m11;
	float m21;
	float m12;
	float m22;
};

struct matrix2x2 current_prob;

void initKalmanPosVel(void)
{
	current_prob.m11 = 1;
	current_prob.m21 = 0;
	current_prob.m12 = 0;
	current_prob.m22 = 1;
}

/*
quadprops.baro_height should be set as the height derived from raw barometer reading every time we have a new reading.  We are then ready to run the Kalman filter every program loop, by calling KalmanPosVel().  Note var_acc and R11 are equivalent to the y-axis and x-axis values respectively in the 2d plots above.  Please experiment with these values yourself - I have not finalised them myself yet!
*/

#define timeslice 0.004 # 250 Hz
#define var_acc 1

void KalmanPosVel(void)
{
	const float Q11=var_acc*0.5*(timeslice*timeslice*timeslice*timeslice);
	const float Q12=var_acc*0.5*(timeslice*timeslice*timeslice);
	const float Q21=var_acc*0.5*(timeslice*timeslice*timeslice);
	const float Q22=var_acc*(timeslice*timeslice);
	const float R11=0.008;

	float ps1,ps2,opt;
	float pp11,pp12,pp21,pp22;
	float inn, ic, kg1, kg2;

	ps1 = quadprops.height  + timeslice * quadprops.kalmanvel_z;
	ps2 = quadprops.kalmanvel_z;

 //ps1 = quadprops.height  + timeslice * quadprops.kalmanvel_z + 0.5*timeslice*timeslice*quadprops.measured_az ;
 //ps2 = quadprops.kalmanvel_z + timeslice*quadprops.measured_az;
 //quadprops.measured_az = 100*9.81*(World_az-gravity)/gravity; // Units are cm/s/s
/*
Where quadprops.measured_az is the World frame vertical (Z-axis) acceleration in cm/s/s.  We need to rotate the accelerometer vector from the quadcopter body frame to the World frame, using our knowledge of the pitch and roll angles (which are themselves derived principally from the gyroscopes).  The World-z acceleration (World_az) can then be converted to SI units using:

# Python code
# pitchr and rollr are the pitch and roll in radians
# ax, ay and az are the accelerometer values for x, y, and z-axis (in the body frame)
      rx = ax*-math.sin(pitchr)
      ry = ay*math.cos(pitchr)*math.sin(rollr)
      rz = az*math.cos(rollr)*math.cos(pitchr)

      World_az = rx + ry + rz

In this simulation, the body ax, ay and az were generated from the pitch and roll angles using the following expressions:

# Python code
        az = math.sqrt((gravity*gravity)/((1+math.tan(pitchr)**2)*(1+math.tan(rollr)**2)))
        ay = az * math.tan(rollr)
        ax = -math.sqrt(ay*ay+az*az)*math.tan(pitchr)

  rx = -ax*sinpitch
      ry = ay*cospitch*sinroll
      rz = az*cosroll*cospitch

      World_az = rx + ry + rz
*/

	opt = timeslice*current_prob.m22;
	pp12 = current_prob.m12 + opt + Q12;

	pp21 = current_prob.m21 + opt;
	pp11 = current_prob.m11 + timeslice * (current_prob.m12 + pp21) + Q11;
	pp21 += Q21;
	pp22 = current_prob.m22 + Q22;

	inn = quadprops.baro_height - ps1;
	ic = pp11 + R11;

	kg1 = pp11/ic;
	kg2 = pp21/ic;

	quadprops.height = ps1 + kg1 * inn;
	quadprops.kalmanvel_z = ps2 + kg2 * inn;

	opt = 1-kg1;
	current_prob.m11 = pp11 * opt;
	current_prob.m12 = pp12 * opt;
	current_prob.m21 = pp21 - pp11 * kg2;
	current_prob.m22 = pp22 - pp12 * kg2;
}
