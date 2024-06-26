using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int x1, x2, height;
        int lowerPointKey = -1, chosenLowerPointIndex = -1, prevLowerPointIndex = -1, lowerPointIndex = -1;
        
        map<int, int> lowerPointIndexes;
        vector<vector<int>> result;

        result.push_back({buildings[0][0], buildings[0][2]});
        lowerPointIndexes[buildings[0][1]] = 0;
        int lastHeight = buildings[0][2], lastX2 = buildings[0][1];

        for (int i = 1; i < buildings.size(); i++) {
            x1 = buildings[i][0];
            x2 = buildings[i][1];
            height = buildings[i][2];

            chosenLowerPointIndex = -1;
            prevLowerPointIndex = -1;
            lowerPointIndex = -1;

            // printf("lower point indexes\n");
            // for (auto keyValue: lowerPointIndexes) {
            //     printf("%d -> %d | ", keyValue.first, keyValue.second);
            // }
            // cout << endl;

            while (!lowerPointIndexes.empty()) {
                lowerPointKey = lowerPointIndexes.begin()->first;
                lowerPointIndex = lowerPointIndexes.begin()->second;
                
                if (buildings[lowerPointIndex][1] > x1) {
                    break;
                }

                if (
                    (prevLowerPointIndex == -1 || buildings[prevLowerPointIndex][2] < buildings[lowerPointIndex][2])
                ) {
                    prevLowerPointIndex = lowerPointIndex;
                    lowerPointIndexes.erase(lowerPointKey);

                } else {
                    if (chosenLowerPointIndex != -1) {
                        result.push_back({buildings[chosenLowerPointIndex][1], buildings[lowerPointIndex][2]});
                        lastX2 = buildings[lowerPointIndex][1];
                        lastHeight = buildings[lowerPointIndex][2];
                    }

                    chosenLowerPointIndex = prevLowerPointIndex;
                    prevLowerPointIndex = -1;
                }
            }

            if (chosenLowerPointIndex == -1 && lowerPointIndex != -1) {
                chosenLowerPointIndex = lowerPointIndex;
                lowerPointIndex = -1;
            }

            if (chosenLowerPointIndex != -1 && lowerPointIndex != -1) {
                result.push_back({buildings[chosenLowerPointIndex][1], buildings[lowerPointIndex][2]});
                
                lastX2 = buildings[lowerPointIndex][1];
                lastHeight = buildings[lowerPointIndex][2];

                chosenLowerPointIndex = lowerPointIndex;
                lowerPointIndex = -1;
            }


            if (chosenLowerPointIndex != -1) {
                result.push_back({buildings[chosenLowerPointIndex][1], 0});
                lastX2 = buildings[chosenLowerPointIndex][1];
                lastHeight = 0;
            }

            // printf("%d %d %d %d\n", lastX2, x1, lastHeight, height);
            if ((lastX2 >= x1 && lastHeight < height) || lastX2 < x1) {
                result.push_back({x1, height});

                lastX2 = x2;
                lastHeight = height;
            }

            lowerPointIndexes[x2] = i;

            
        }

        // cout << lowerPointIndexes.size() << endl;

        chosenLowerPointIndex = -1;
        prevLowerPointIndex = -1;
        lowerPointIndex = -1;

        while (!lowerPointIndexes.empty()) {
            lowerPointKey = lowerPointIndexes.begin()->first;
            lowerPointIndex = lowerPointIndexes.begin()->second;

            if (
                (prevLowerPointIndex == -1 || buildings[prevLowerPointIndex][2] < buildings[lowerPointIndex][2])
            ) {
                prevLowerPointIndex = lowerPointIndex;
                lowerPointIndexes.erase(lowerPointKey);

            } else {
                if (chosenLowerPointIndex != -1) {
                    result.push_back({buildings[chosenLowerPointIndex][1], buildings[lowerPointIndex][2]});
                }

                chosenLowerPointIndex = prevLowerPointIndex;
                prevLowerPointIndex = -1;
            }
        }

        if (chosenLowerPointIndex == -1 && lowerPointIndex != -1) {
            chosenLowerPointIndex = lowerPointIndex;
            lowerPointIndex = -1;
        }

        if (chosenLowerPointIndex != -1 && lowerPointIndex != -1) {
            result.push_back({buildings[chosenLowerPointIndex][1], buildings[lowerPointIndex][2]});
            chosenLowerPointIndex = lowerPointIndex;
            lowerPointIndex != -1;
        }

        if (chosenLowerPointIndex != -1) {
            result.push_back({buildings[chosenLowerPointIndex][1], 0});
        }

        return result;
    }
};