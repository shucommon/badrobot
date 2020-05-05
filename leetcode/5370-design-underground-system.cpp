/*
UndergroundSystem undergroundSystem = new UndergroundSystem();
undergroundSystem.checkIn(45, "Leyton", 3);
undergroundSystem.checkIn(32, "Paradise", 8);
undergroundSystem.checkIn(27, "Leyton", 10);
undergroundSystem.checkOut(45, "Waterloo", 15);
undergroundSystem.checkOut(27, "Waterloo", 20);
undergroundSystem.checkOut(32, "Cambridge", 22);
undergroundSystem.getAverageTime("Paradise", "Cambridge");       // 返回 14.0。从 "Paradise"（时刻 8）到 "Cambridge"(时刻 22)的行程只有一趟
undergroundSystem.getAverageTime("Leyton", "Waterloo");          // 返回 11.0。总共有 2 躺从 "Leyton" 到 "Waterloo" 的行程，编号为 id=45 的乘客出发于 time=3 到达于 time=15，编号为 id=27 的乘客于 time=10 出发于 time=20 到达。所以平均时间为 ( (15-3) + (20-10) ) / 2 = 11.0
undergroundSystem.checkIn(10, "Leyton", 24);
undergroundSystem.getAverageTime("Leyton", "Waterloo");          // 返回 11.0
undergroundSystem.checkOut(10, "Waterloo", 38);
undergroundSystem.getAverageTime("Leyton", "Waterloo");          // 返回 12.0
*/
/*
总共最多有 20000 次操作。
1 <= id, t <= 10^6
所有的字符串包含大写字母，小写字母和数字。
1 <= stationName.length <= 10
与标准答案误差在 10^-5 以内的结果都视为正确结果。
*/

typedef struct info {
    int id; 
    string name; 
    int t; 
} info_t;

class UndergroundSystem {
public:
    UndergroundSystem() {
        
    }
    
    void checkIn(int id, string stationName, int t) {
        info_t tmp;
        tmp.id = id;
        tmp.name = stationName;
        tmp.t = t;
        people_in.push_back(tmp);
    }
    
    void checkOut(int id, string stationName, int t) {
        info_t tmp;
        tmp.id = id;
        tmp.name = stationName;
        tmp.t = t;
        people_out.push_back(tmp);
    }
    
    double getAverageTime(string startStation, string endStation) {
        int total_t = 0, cnt = 0;
        vector<info>::iterator ito = people_out.begin();
        for(vector<info>::iterator it = people_in.begin(); it != people_in.end(); it++) {
            if(it->name == startStation) {
                for(; ito != people_out.end(); ito++) {
                    if(ito->id == it->id && ito->name == endStation) {
                        total_t += (ito->t - it->t);
                        cnt++;
                        break;
                    }
                }
            }
        }
        if(cnt)
            return (float(total_t)/float(cnt));
        return 0;
    }

private:
    vector<info> people_in;
    vector<info> people_out;
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
