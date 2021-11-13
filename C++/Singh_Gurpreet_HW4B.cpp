//AUTHOR: GURPREET SINGH
#include <ctime>
#include <iostream>

using namespace std; 

class JulianDate { //https://quasar.as.utexas.edu/BillInfo/JulianDatesG.html
private:
	static int EPOCH;
	double mon, day, year, hour, min, second;
	// this representation would make difference VERY UGLY
	// diff between Jan. 1 2001 12:03:04  and Feb 26 2028 11:19:02
	double jday; // number of days since epoch
public:
    JulianDate(double year, double mon, double day, double hour, double min, double second) 
    :  year(year), mon(mon), day(day), hour(hour), min(min), second(second) {
         cout << year << "/" << mon << "/" << day << " "
         << hour << ":" << min << ":" << second << '\n'; 
    }
    JulianDate()  { //year(), mon(), day(), hour(), min(), second()
        time_t today = time(0); //system time
        tm* now = localtime(&today);
        /* this->year = now->tm_year;
        cout << this->year; */
    
        cout << (now->tm_year + 1900) << '/' 
         << (now->tm_mon + 1) << '/'
         << now->tm_mday << ' '
         << now->tm_hour << ':'
         << now->tm_min << ':'
         << now->tm_sec
         << "\n"; 
        //JulianToGreg(today, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
        //JulianCalc(today, now->tm_year, now->tm_mon, now->tm_mday);
    }
    int getYear() {
        return this->year;
    }
    int getMonth() {
        return this->mon;
    }
    int getDay() {
        return this->day;
    }
    int getHour() {
        return this->hour;
    }
    int getMin() {
        return this->min;
    }
    int getSec() {
        return this->second;
    } 
    double JulianCalc(JulianDate calc) const {
        int I = calc.getYear();
        int J = calc.getMonth();
        int K = calc.getDay();

        double JD = K - 32075 + 1461*(I + 4800 + (J-14)/12)/4 + 367 * 
                (J - 2 - (J - 14)/12 * 12)/12 - 3 * ((I + 4900 + (J - 14)/12)/100)/4;
        return JD;
    }

    double JulianToGreg(double JD, double year, double mon, double day, double hour, double min, double second) {
        int L = JD+68569;
        int N = 4*L/146097;
        L = L-(146097*N+3)/4;
        int I = 4000*(L+1)/1461001;
        L = L-1461*I/4+31;
        int J = 80*L/2447;
        int K = L-2447*J/80; //day
        L = J/11; 
        J = J+2-12*L; //month
        I = 100*(N-49)+I+L; //year
        day = K;
        mon = J;
        year = I;
        //cout << "total: " << I + J + K << endl;
        JulianDate(I, J, K, hour, min, second);
    }
    double JulianToGreg(double JD) {
        int L = JD+68569;
        int N = 4*L/146097;
        L = L-(146097*N+3)/4;
        int I = 4000*(L+1)/1461001;
        L = L-1461*I/4+31;
        int J = 80*L/2447;
        int K = L-2447*J/80; //day
        L = J/11; 
        J = J+2-12*L; //month
        I = 100*(N-49)+I+L; //year
        cout << I << "/" << J << "/" << L << endl;
    }

    double daysSinceEpoch(JulianDate date) {
        jday = 365 * (date.getYear() - EPOCH) + date.getYear()/4 - date.getYear()/100 + date.getYear()/400;
        return jday;
    }
    friend ostream& operator <<(ostream& s, const JulianDate& date);
    friend const JulianDate operator -(JulianDate& a, JulianDate& b);
    friend const JulianDate operator +(JulianDate& a, int b);
};

    ostream& operator <<(ostream&s, const JulianDate& d) {
         return s;
         //<< d.year << "/" << d.mon << "/" << d.day << " "
         //<< d.hour << ":" << d.min << ":" << d.second << '\n';
    }

    const JulianDate operator -(JulianDate& a, JulianDate& b) {
        double JD;
        JD = a.JulianCalc(a) - b.JulianCalc(b); 
        a.JulianToGreg(JD);
    } 
 
    const JulianDate operator +(JulianDate& a, int b) {
        double JD;
        JD = a.JulianCalc(a) + b; 
        a.JulianToGreg(JD, a.year, a.mon, a.day, a.hour, a.min, a.second);
    }

    /* JulianDate operator -(JulianDate& a, JulianDate& b) {
        return JulianDate(a.year - b.year, a.mon - b.mon, a.day - b.day, 
        a.hour - b.hour, a.min - b.min, a.second - b.second);
    }  */
/*
	how many days in a year? 365
	leap year: if year MOD 4 == 0 LEAP EXCEPT
	           if year MOD 100 == 0 NOT LEAP YEAR Except
						 if year MOD 400 == 0 LEAP

Leap years:
 NO 1900 
 YES 1904
 YES 1908
 YES 2000
 NO 2100
 YES 2400

    days since EPOCH = 365 * (year - 2000) + years/4 - ....

2018 - 2000 = 18

seconds in a day = 24*60*60 = 86400

hh:mm:ss     

00:00:00  0.0
12:00:00  0.5

http://aa.usno.navy.mil/faq/docs/JD_Formula.php
http://www.math.harvard.edu/~knill/3dprinter/exhibits/bc/Meeus1988.pdf
 */



int JulianDate::EPOCH = 2000; // Jan.1 2000, 00:00:00 = 0

int main() {
	JulianDate newyear(2018, 1, 1, 0,0,0);
	JulianDate valentine(2018, 2, 14, 12,0,0); // 0.5
	JulianDate today; // get it from the system time: time(nullptr)
	                  // localtime

	//double days = valentine - newyear;
	JulianDate due = today + 7;
	cout << due << '\n';

	cout << "\nyear: " << newyear.getYear()
			 << "\nmonth: " << newyear.getMonth()
			 << "\nday: " << newyear.getDay()
			 << "\nhour: " << newyear.getHour()
			 << "\nmin: " << newyear.getMin()
			 << "\nsec: " << newyear.getSec() << '\n';
	JulianDate d1(2019, 1, 1, 0,0,0);
	for (int i = 0; i < 100; i++)
		cout << d1 + i;

}

		
