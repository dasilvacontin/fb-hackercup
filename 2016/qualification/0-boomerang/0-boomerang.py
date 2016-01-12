from collections import namedtuple, defaultdict
from itertools import combinations
from math import factorial

Star = namedtuple("Star", "x y")

def distSS(s1, s2):
  return (s2.x - s1.x)**2 + (s2.y - s1.y)**2 # avoid doing sqrt ftw?

# http://stackoverflow.com/questions/3025162/statistics-combinations-in-python
def choose(n, k):
    """
    A fast way to calculate binomial coefficients by Andrew Dalke (contrib).
    """
    if 0 <= k <= n:
        ntok = 1
        ktok = 1
        for t in xrange(1, min(k, n - k) + 1):
            ntok *= n
            ktok *= t
            n -= 1
        return ntok // ktok
    else:
        return 0

def count_boomerangs(stars, scount):
  booms = 0
  for i in xrange(scount):
    s1 = stars[i]
    dts = defaultdict(list) # dist to star
    for j in xrange(scount):
      if i == j: continue
      s2 = stars[j]
      dts[distSS(s1, s2)].append(s2)
    for dist, ends in dts.iteritems():
      count = len(ends)
      """
      if count < 2: continue
      booms += factorial(count) / 2 / factorial(count - 2)
      """
  return booms

nights = int(raw_input())
for n in xrange(nights):
  stars = []
  scount = int(raw_input())
  for _ in xrange(scount):
    coords = map(int, raw_input().split())
    star = Star(coords[0], coords[1])
    stars.append(star)
  print "Case #%d: %d" % (n + 1, count_boomerangs(stars, scount))
