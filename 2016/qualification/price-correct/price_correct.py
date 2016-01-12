def combinations(N, P, boxes):
  combs = 0
  sum = 0
  b = 0
  e = 0
  while e < N:
    sum += boxes[e]
    while sum > P:
      sum -= boxes[b]
      b += 1
    combs += (e - b) + 1
    e += 1
  return combs

S = int(raw_input())
for s in xrange(S):
  NP = map(int, raw_input().split())
  N = NP[0]
  P = NP[1]
  boxes = map(int, raw_input().split()) # probably slow for long lines
  print "Case #%d: %d" % (s + 1, combinations(N, P, boxes))
