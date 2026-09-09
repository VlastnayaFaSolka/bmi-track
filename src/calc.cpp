#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void swap_data(float &data_1, float &data_2);
void init_test_data(float &acl, float &gyr, long &t, ifstream &file);
void calc_data_err(float &data, float &err, float EPS);

int main() {
	//all arr have struct VAR_NAME[3] = {X, Y, Z}
    float acl_1[3], acl_2[3];
    float gyr_1[3], gyr_2[3];
    float dv_1[3], dv_2[3];
    float ds[3];
    double cords[3] = {0, 0, 0}, V[3] = {0, 0, 0};
    long t1, t2, dt; 

    ifstream file("test_data.txt");
    if (file) {

    	//we get the data required for the calculation
    	init_test_data(*acl_1, *gyr_1, t1, file);

        swap_data(*acl_1, *acl_2);
        swap_data(*gyr_1, *gyr_2);
        t2 = t1;
        init_test_data(*acl_1, *gyr_1, t1, file);
        dt = t1 - t2;
        for (int i = 0; i < 3; i++){
        	dv_1[i] = acl_1[i]+acl_2[i]/2*dt;
        	V[i] += dv_1[i];
        }
        swap_data(*dv_1, *dv_2);

        while (true) {
            if (file.eof()) {
                break;
            }

            swap_data(*acl_1, *acl_2);
            swap_data(*gyr_1, *gyr_2);
            t2 = t1;
            init_test_data(*acl_1, *gyr_1, t1, file);
            dt = t1 - t2;
            for (int i = 0; i < 3; i++){
            	dv_1[i] = acl_1[i]+acl_2[i]/2*dt;
            	V[i] += dv_1[i];
            }
            swap_data(*dv_1, *dv_2);

            for (int i = 0; i < 3; i++){
            	ds[i] = ((dv_1[i]+dv_2[i])/2 + V[i])*dt;
            	cords[i] += ds[i];
            }
			printf("%f %f %f\n", cords[0], cords[1], cords[2]);
	// 		for (int i = 0; i < 10-1; i++){
	// 			ds[i] = ((dv[i]+dv[i+1])/2 + V)*dt;
	// 			cout << ds[i] << endl;
			// }
        }
    }

    return 0;
}

//assigns data_1 to data_2 
void swap_data(float &data_1, float &data_2){
	for (int i = 0; i < 3; i++){
		*(&data_2+i) = *(&data_1+i);
	}
}

//get data from file
void init_test_data(float &acl, float &gyr, long &t, ifstream &file){
	float ax, ay, az, gx, gy, gz;
	//measurement errors
	float acl_err[3] = {-0.79, 0.085, 0.61};
    float gyr_err[3] = {0.1, 0.1, 0.01};
    float EPS = 0.01;

	file >> ax >> ay >> az >> gx >> gy >> gz >> t;
	*(&acl + 0) = ax; *(&acl + 1) = ay; *(&acl + 2) = az;
	*(&gyr + 0) = gx; *(&gyr + 1) = gy; *(&gyr + 2) = gz;
	calc_data_err(acl, *acl_err, EPS);

	t /= 1000;
}
//calculate err
void calc_data_err(float &data, float &err, float EPS){
	// float EPS = 0.01;
	for (int i = 0; i < 3; i++){
		*(&data + i) -= *(&err + i);
		if (*(&data + i) < EPS){
			*(&data + i) = 0;
		}
	}
}