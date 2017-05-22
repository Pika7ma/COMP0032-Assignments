#include <iostream>
#include <vector>
#define INF 9999999 // ����һ���޷��ﵽ�Ĵ�ֵ����ǰ��Ӳ������͸����޷��ճ�Ҫ��Ľ��
using namespace std;

int main() {

    // ��ʼ������
    int valueNum = 0; // �������
    int finalMoney = 0; // Ŀ����
    cin >> valueNum; // �����������
    vector<int> values(valueNum); // ��¼����Ӳ�ҵ����
    vector<int> numbers(valueNum); // ��¼�����Ӳ�ҵ�����
    for (int i = 0; i < valueNum; ++i) {
        cin >> values[i] >> numbers[i]; // �������Ӳ�ҵ���������
    }
    cin >> finalMoney; // ����Ŀ����

                       // ��ƶ�̬�滮����[����ǰi�����, ǡ�ôﵽ�ܶ�j] := ��������������Ӳ����
    vector<vector<int> > dp(valueNum + 1, vector<int>(finalMoney + 1, 0)); // �����ά��̬�滮���鲢
    for (int i = 1; i <= finalMoney; ++i) {
        dp[0][i] = INF; // ��ʼ��Ϊ[0, INF, INF, ...]
    }

    //            { dp[i - 1, j] when ���i�޷�����Ҫ�� (1)
    // dp[i, j] = {
    //            { min(dp[i - 1, j - k * i�����] + k) when 1 <= k <= i���Ӳ�ҵ����� and k * i����� > j (2)

    for (int i = 1; i <= valueNum; ++i) {
        for (int j = 1; j <= finalMoney; ++j) {
            int min = INF; // �ϲ�(1)(2)��� ���޷�����Ҫ���� k = 0 ����Сֵ
            for (int k = 0; k <= numbers[i - 1]; ++k) {
                if (j - k * values[i - 1] < 0) break; // ��k����������Ӳ�ҵ��ܽ������趨�ܶ�j������
                if (min > dp[i - 1][j - k * values[i - 1]] + k) {
                    min = dp[i - 1][j - k * values[i - 1]] + k;
                }
            }
            dp[i][j] = min; // Ϊ�丳��ֵ
        }
    }
    cout << ((dp[valueNum][finalMoney] == INF) ? -1 : dp[valueNum][finalMoney]) << endl; // �������ǡ�ôﵽfinalMoney��Ӳ������ΪINF��˵���޷����
    return 0;
}