#include <iostream>
#include <mutex>
#include <thread>
#include <deque>
#include <string>

struct ManyCarsInOneRoad{
	std::string message;
    ManyCarsInOneRoad(const std::string& msg) : message(msg) {}
};

struct ManyCarsInCross{
	std::string message;
     ManyCarsInCross(const std::string& msg) : message(msg) {}
};

void out(int N, int S, int W, int E){
	std::mutex m;
	std::lock_guard<std::mutex> lg(m);
	if(N != 0){
	std::cout << "car drive on road 1\n";
	}
	if(S != 0){
		std::cout << "car drive on road 2\n";
	}
	if(E != 0){
		std::cout << "car drive on road 3\n";
	}
	if(W != 0){
		std::cout << "car drive on road 4\n";
	}	
}

void road(int N, int S, int E, int W){
	if(N != 0 || S != 0){
		std::cout << "green on road A\n";
	}
	if(E != 0 || W != 0){
		std::cout << "green on road B\n";
	}
	
	while(N > 0){
		std::jthread pusht(out, N, S, W, E);
		N--;
	}
	while(S > 0){
		std::jthread pusht1(out, N, S, W, E);
		S--;
	}
	while(W > 0){
		std::jthread pusht2(out, N, S, W, E);
		W--;
	}
	while(E > 0){
		std::jthread pusht3(out, N, S, W, E);
		E--;
	}
	
}

void ss_check(int i, std::deque<int>::iterator start, std::deque<int>::iterator end){
		int N = 0;
		int S = 0;
		int W = 0;
		int E = 0;
	    for(auto it = start; it <= end; ++it) {
        if(*it == 2){
			N++;
			if(N <= 2){
				it++;
				if(it <= end){
					if(*it == 3 || *it == 4){
						throw ManyCarsInCross("Many cars on the cross!");
					}
				}
				it--;
		}else{
			throw ManyCarsInOneRoad("Many cars on the road N!");
		}
	}
	
		if(*it == 1){
			S++;
			if(S <= 2){
				it++;
				if(it <= end){
					if(*it == 3 || *it == 4){
						throw ManyCarsInCross("Many cars on the cross!");
					}
				}
				it--;
			}else{
				throw ManyCarsInOneRoad("Many cars on the road s!");
			}
		}
		if(*it == 3){
			W++;
			if(W <= 1){
				it++;
				if(it <= end){
					if(*it == 2 || *it == 1){
						throw ManyCarsInCross("Many cars on the cross!");
					}
				}
				it--;
			}else{
				throw ManyCarsInOneRoad("Many cars on the road E!");
			}
		}
		 if(*it == 4){
			 E++;
			if(E <= 1){
				it++;
				if(it <= end){
					if(*it == 1 || *it == 2){
						throw ManyCarsInCross("Many cars on the cross!");
					}
			}
			it--;
			}else{
				throw ManyCarsInOneRoad("Many cars on the road W!");
			}
		}
    
	}
	
road(N, S, E, W);
}

int main(){
	std::deque<int> t = {1, 1, 1, 1, 2, 2};
	std::deque<int> ss = {1, 1, 1, 2, 3, 4};
	int o = 1;
	while(!t.empty()){
		if(t[0] == t[1]){
			o++;
			t.pop_front();
		}else {
			t.pop_front();
			try{
			ss_check(o, ss.begin(), ss.begin() + o - 1);
			}	
    catch (const ManyCarsInCross& e) {
        std::cout << e.message << std::endl;
        return -1;
    }
    catch (const ManyCarsInOneRoad& e) {
        std::cout << e.message << std::endl;
        return -1;
    }
			ss.erase(ss.begin(), ss.begin() + o );
			o = 1;
		}
	} 
}
