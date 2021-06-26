/*  Copyright (C) 2021 @lyazj
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "CTjson.h"

#include <vector>
#include <map>

using namespace CTjson;
using namespace std;

template<class T>
inline auto operator<<(ojsonstream &ojs, const T &t)
  -> decltype(t.print(ojs))
{
  return t.print(ojs);
}

#define KVP(var) #var, var

struct Province {
  string name;
  vector<string> cities;

  ojsonstream &print(ojsonstream &ojs) const
  {
    return prt_obj(ojs, KVP(name), KVP(cities));
  }
};

struct Country {
  string name;
  vector<Province> provinces;

  ojsonstream &print(ojsonstream &ojs) const
  {
    return prt_obj(ojs, KVP(name), KVP(provinces));
  }
};

int main()
{
  ojsonstream ojs(cout.rdbuf());
  ojs << nullptr << endl;
  ojs << string("STL-string") << endl;
  ojs << "Cstyle-string" << endl;
  ojs << (const char *)NULL << endl;
  ojs << 1 << endl;
  ojs << 1.0 << endl;
  ojs << true << endl;
  ojs << vector<int>{1, 2, 3} << endl;
  ojs << map<string, int>{{"a", 1}, {"b", 2}} << endl;
  ojs << Country {
    "中国", {
      {"黑龙江", {"哈尔滨", "大庆"}},
      {"广东", {"广州", "深圳", "珠海"}},
      {"台湾", {"台北", "高雄"}},
      {"新疆", {"乌鲁木齐"}},
    }
  } << endl;
}
