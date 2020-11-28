#include <jni.h>
//#include <cstring>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <sstream>
#include <string>
#include <vector>

//using namespace std;
bool is_divisible(unsigned int num, unsigned int by_num)
{
	if(num % by_num)
		return false;
	else
		return true;
}

struct Prime
{
	private:
		unsigned int prime_from;
		unsigned int third_count = 0;
	public:

	Prime(unsigned int number){prime_from = number;}
	Prime(){prime_from = 2;}

	bool is_prime(unsigned int number)
	{
		unsigned int square_root = ((unsigned int)sqrt(number)) + 1;
		if(!(number%2))
			return false;
		unsigned int third_count = 0;
		unsigned int count = 3;
		while(count < square_root){
			if (!(number%count))
				return false;
			if(third_count==2){
				count += 4;
				third_count = 0;
			}
			else{
				count+=2;
			}
			third_count += 1;
		}
		return true;
	}

	unsigned int generate_prime()
	{
		if(prime_from == 2)
		{
			prime_from = 3;
			return 2;
		}
		static unsigned int temp = 0;
		while(prime_from < UINT_MAX)
		{
			if(third_count==3){
				third_count = 1;
				prime_from += 2;
			}
			third_count++;
			if(Prime::is_prime(prime_from)){

				temp = prime_from;
				prime_from += 2;
				return temp;
			}
			prime_from += 2;
		}
		return 1;
	}

	void set_prime_from(unsigned int number)
	{
		if(number == 2)
			prime_from = 2;
		else if(!(number % 2))
			prime_from = number + 1;
		else
			prime_from = number;

	}

	unsigned int get_prime_from(void){return prime_from;}
};

//Data structure used by the prime_factorize function to store prime factors of a numeber
//
struct EachFactor
{
	unsigned int number;
	unsigned int power;
};

std::vector<EachFactor> prime_factorize(unsigned int number)
{
	Prime p{};
	unsigned int factors_size = 10;
	unsigned int each_prime;
	EachFactor each_factor{};
	std::vector<EachFactor> factors;
	while(number > 1)
	{
		each_prime = p.generate_prime();
		each_factor = {each_prime, 0};
		while(is_divisible(number, each_prime))
		{
			number /= each_prime;
			each_factor.power++;
		}
		if(each_factor.power > 0)
			factors.push_back(each_factor);
	}
	return factors;
}

std::string getFactorsOutputPower(const std::vector<EachFactor>& factors){
	std::ostringstream os;
	for(auto iter=factors.begin(); iter!=factors.end(); iter++)
		os << iter->number << '^' << iter->power << " x ";
	std::string output = os.str();
	return output.substr(0, output.size()-3);
}

std::string getFactorsOutput(const std::vector<EachFactor>& factors){
	std::ostringstream os;
	for(auto iter=factors.begin(); iter!=factors.end(); iter++){
		for(int i=0; i < iter->power; i++)
			os << iter->number << " x ";
	}
	std::string output = os.str();
	return output.substr(0, output.size()-3);
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_phantom_automath_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject obj) {
    std::string hello = "Numbers: ";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_phantom_automath_MainActivity_Factorize(
        JNIEnv* env,
        jobject obj, jint integer, jint in_power){
            std::vector<EachFactor> vec = prime_factorize((unsigned int)integer);
            std::string output;
            if((int)in_power != 0)
                output = getFactorsOutputPower(vec).c_str();
            else
                output = getFactorsOutput(vec).c_str();
            return env->NewStringUTF(output.c_str());
        }
