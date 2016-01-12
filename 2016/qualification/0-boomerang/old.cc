#include <iostream>
#include <vector>
#include <map>
#include <math.h>
using namespace std;

struct Star {
  int x;
  int y;
  Star (int x, int y) : x (x), y (y) {}
  void log () {
    cout << "[Star] x:" << this->x << " y: " << this->y << " ";
  }
};

int distSS(Star *s1, Star *s2) {
  return (s2->x - s1->x) + (s2->y - s1->y);
}

struct Line {
  Star *s1;
  Star *s2;
  int length;
  float elength;
  Line (Star *s1, Star *s2) : s1 (s2), s2 (s1) {
    this->elength = -1;
    if (s1->x < s2 ->x || (s1->x == s2->x && s1->y < s2->y)) {
      this->s1 = s1;
      this->s2 = s2;
    }
    this->length = distSS(this->s1, this->s2);
  }
  float getEucledianDistance() {
    float elength = this-> elength;
    if (elength != -1) {
      return elength;
    }
    elength = round(sqrt(pow(s2->x - s1->x, 2) + pow(s2->y - s1->y, 2)));
    this->elength = elength;
    return elength;
  }
  void log () {
    cout << "[Line] length:" << this->length;
    cout << ", elength:" << this->elength << " ";
    this->s1->log();
    this->s2->log();
    cout << endl;
  }
};

bool haveStarInCommon(Line *l1, Line *l2) {
  return (
    l1->s1 == l2->s1 ||
    l1->s1 == l2->s2 ||
    l1->s2 == l2->s1 ||
    l1->s2 == l2->s2
  );
}

bool haveSameEucledianDistance(Line *l1, Line *l2) {
  return l1->getEucledianDistance() == l2->getEucledianDistance();
}

typedef vector<Star> vS;
typedef vector<Line> vLine;

int main () {
  int T, t;
  int N, n;
  int x, y;

  cin >> T;
  for (t = 1; t <= T; ++t) {
    // if (t > 2) break;
    cin >> N;
    vS stars;
    map<int, vLine> lines;
    int boomerangs = 0;

    // get all stars from input
    for (n = 0; n < N; ++n) {
      cin >> x >> y;
      Star s(x, y);
      stars.push_back(s);
    }

    // create combinations of lines and store them by their cartesian length
    int i, j;
    Star *s1, *s2;
    for (i = 0; i < N; ++i) {
      s1 = &stars[i];
      for (j = i + 1; j < N; ++j) {
        s2 = &stars[j];
        Line l(s1, s2);
        lines[l.length].push_back(l);
      }
    }

    // iterate lines of same cartesian length (cant have same actual length if
    // cartesian length is different)
    for(map<int, vLine>::iterator it = lines.begin(); it != lines.end(); ++it) {
      vLine *ls = &(it->second);
      Line *l1, *l2;
      for (size_t i = 0; i < ls->size(); ++i) {
        l1 = &(*ls)[i];
        for (size_t j = i + 1; j < ls->size(); ++j) {
          l2 = &(*ls)[j];
          if (haveStarInCommon(l1, l2) && haveSameEucledianDistance(l1, l2)) {
            // l1->log();
            // l2->log();
            // cout << "=========" << endl;
            ++boomerangs;
          }
        }
        l1->log();
      }
    } // end for n in N (stars)
    cout << "Case #" << t << ": " << boomerangs << endl;
  } // end for t in T
}
