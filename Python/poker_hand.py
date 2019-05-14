from itertools import groupby
from collections import Counter

def rank_hand(lis):
    face_cards = {'A': 14, 'K': 13, 'Q': 12, 'J': 11, 'T': 10,}
    suits = []
    cards = []
    for k, v in lis:
        if k in face_cards:
             cards.append(face_cards.get(k))
        else:
            cards.append(int(k))
        suits.append(v)

    s_cards = sorted(cards)
    l_cards = len(s_cards)
    l_set_suits = len(set(suits))

    for k, v in groupby(s_cards):
        print(k)
        print(list(v))

    if l_set_suits == 1: #one sort
        if sum(s_cards) == 60: # royal flush
            return 9
        elif s_cards[4] == 14: # straight flush with ace
            s_cards[4] = 1
            if max(s_cards) - min(s_cards) == l_cards - 1:
                return 8
            else:
                return 5
        elif max(s_cards) - min(s_cards) == l_cards - 1: #without ace
            return 8
        else: #flush
            return 5
    elif [k for k, v in groupby(s_cards) if len(list(v)) == 4]: #four of a kind
        return 7
    elif [k for k, v in groupby(s_cards) if len(list(v)) == 3]:
            if [k for k, v in groupby(s_cards) if len(list(v)) == 2]: #full house
                return 6
            else:       #three of a kind
                return 3
    elif [k for k, v in groupby(s_cards) if len(list(v)) == 2]:
         pair = [x for x, count in Counter(s_cards).items() if count >= 2]
         if(len(pair) == 2): #two pairs
             return 2
         else: #one pair
             return 1
    elif max(s_cards) - min(s_cards) == l_cards - 1: #Straight
        return 4
    elif s_cards[4] == 14:
        temp = s_cards[4]
        s_cards[4] = 1
        if max(s_cards) - min(s_cards) == l_cards - 1:
            return 4
        s_cards[4] = temp
        if max(s_cards) - min(s_cards) == l_cards - 1:
            return 4
        else: # high card
            return 0
    else: #high card
        return 0

print(rank_hand(['9C', 'JH', 'JC', 'QC', '8D']))
