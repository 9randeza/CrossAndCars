#include <iostream>
#include <mutex>
#include <thread>
#include <deque>
#include <string>

bool trafLight = true;

struct ManyCarsInOneRoad{
	std::string message;
    ManyCarsInOneRoad(const std::string& msg) : message(msg) {}
};

struct ManyCarsInCross{
	std::string message;
    ManyCarsInCross(const std::string& msg) : message(msg) {}
};

void out(int i, int N, int S, int W, int E){
	if(N != 0){
		std::cout << i << " car drive on road 2\n";
	}
	if(S != 0){
		std::cout << i <<  " car drive on road 1\n";
	}
	if(W != 0){
		std::cout << i << " car drive on road 3\n";
	}
	if(E != 0){
		std::cout << i << " car drive on road 4\n";
	}	
}

void road(int N, int S, int W, int E, int* n, int* s, int* w, int* e){
	if((N != 0 || S != 0) && trafLight == false){
		std::cout << "green on road A\n";
		trafLight = true;
	}
	if((E != 0 || W != 0) && trafLight == true){
		std::cout << "green on road B\n";
		trafLight = false;
	}
	

	while(S > 0){
		std::jthread pusht1(out, s[S - 1], 0, S, 0, 0);
		S--;
	}
	while(N > 0){
		std::jthread pusht(out, n[N - 1], N, 0, 0, 0);
		N--;
	}
	while(W > 0){
		std::jthread pusht2(out, w[W - 1], 0, 0, W, 0);
		W--;
	}
	while(E > 0){
		std::jthread pusht3(out, e[E - 1], 0, 0, 0, E);
		E--;
	}
	
}

void ss_check(int i, std::deque<std::pair<int, int>>::iterator start, std::deque<std::pair<int, int>>::iterator end){
		int N = 0;
		int S = 0;
		int W = 0;
		int E = 0;
		int n[3];
		int s[3];
		int w[2];
		int e[2];
	    for(auto it = start; it <= end; ++it){
			if((*it).first == 2){
				N++;
				n[N - 1] = (*it).second;
				if(N <= 2){
					it++;
					if(it <= end){
						if((*it).first == 3 || (*it).first == 4){
							throw ManyCarsInCross("Many cars on the cross!");
						}
					}
					it--;
			}else{
				throw ManyCarsInOneRoad("Many cars on the road N!");
			}
		}
	
		if((*it).first == 1){
			S++;
			s[S - 1] = (*it).second;
			if(S <= 2){
				it++;
				if(it <= end){
					if((*it).first == 3 || (*it).first == 4){
						throw ManyCarsInCross("Many cars on the cross!");
					}
				}
					it--;
				}else{
				throw ManyCarsInOneRoad("Many cars on the road S!");
				}
		}
		if((*it).first == 3){
			W++;
			w[W - 1] = (*it).second;
			if(W <= 1){
				it++;
				if(it <= end){
					if((*it).first == 2 || (*it).first == 1){
						throw ManyCarsInCross("Many cars on the cross!");
					}
				}
				it--;
			}else{
				throw ManyCarsInOneRoad("Many cars on the road W!");
			}
		}
		 if((*it).first == 4){
			 E++;
			 e[E - 1] = (*it).second;
			if(E <= 1){
				it++;
				if(it <= end){
					if((*it).first == 1 || (*it).first == 2){
						throw ManyCarsInCross("Many cars on the cross!");
					}
			}
			it--;
			}else{
				throw ManyCarsInOneRoad("Many cars on the road E!");
			}
		}
    
	}
	
	road(N, S, W, E, n, s, w, e);
}

int main(){
	std::deque<int> t = {1, 1, 1, 1, 2};
	std::deque<std::pair<int, int>> ss = {{1,1}, {2, 2}, {2, 3}, {1, 4}, {3, 5}};
	int o = 1;
	try{
		while(!t.empty()){
			if(t[0] == t[1]){
				o++;
				t.pop_front();
			}else {
				t.pop_front();
				ss_check(o, ss.begin(), ss.begin() + o - 1);
				ss.erase(ss.begin(), ss.begin() + o );
				o = 1;
			}
		}
	}
	catch (const ManyCarsInCross& e) {
        std::cout << e.message << std::endl;
        return -1;
    }
    catch (const ManyCarsInOneRoad& e) {
        std::cout << e.message << std::endl;
        return -1;
    }
	return 0;
}

