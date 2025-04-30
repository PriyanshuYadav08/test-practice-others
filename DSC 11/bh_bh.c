#include <stdio.h>
int main()
{
    char *stations[] = {"Dhanbad Junction", "New Jalpaiguri", "Mathura Junction ", " Hisar ", " Shimla ", " Dhaka Cantonment ", " Patna Jn ", " ShahibJada Asngr ", " Ramnagar ", " Howrah Junction ", " Bhopal Jn ", " Guwahati ", " Bilaspur Jn ",
                        "Jaipur"};
    char *stationcodes[] = {"DHN", "NJP", "MTJ", "HSR", "SML", "DAKA", "PNBE",
                            "SASN", "RMR", "HWH", "BPL", "GHY", "BSP", "JP"};
    int distances[14][14];
    int prices[14][14];
    for (int i = 0; i < 14; i++)
    {
        distances[i][i] = 0;
        prices[i][i] = 0;
    }
    distances[0][1] = 575;
    prices[0][1] = 945;
    distances[0][2] = 1200;
    prices[0][2] = 1490;
    distances[0][3] = 1371;
    prices[0][3] = 3145;
    distances[0][4] = 1548;
    prices[0][4] = 2275;
    distances[0][5] = 875;
    prices[0][5] = 10000;
    distances[0][6] = 291;
    prices[0][6] = 505;
    distances[0][7] = 1372;
    prices[0][7] = 1565;
    distances[0][8] = 1117;
    prices[0][8] = 1385;
    distances[0][9] = 263;
    prices[0][9] = 555;
    distances[0][10] = 1226;
    prices[0][10] = 1460;
    distances[0][11] = 962;
    prices[0][11] = 1265;
    distances[0][12] = 643;
    prices[0][12] = 980;
    distances[0][13] = 1244;
    prices[0][13] = 1535;

    distances[1][2] = 1670;
    prices[1][2] = 1500;
    distances[1][3] = 1660;
    prices[1][3] = 1775;
    distances[1][4] = 1731;
    prices[1][4] = 2520;
    distances[1][5] = 1020;
    prices[1][5] = 3500;
    distances[1][6] = 632;
    prices[1][6] = 970;
    distances[1][7] = 1647;
    prices[1][7] = 1760;
    distances[1][8] = 1668;
    prices[1][8] = 2155;
    distances[1][9] = 567;
    prices[1][9] = 895;
    distances[1][10] = 1594;
    prices[1][10] = 1720;
    distances[1][11] = 411;
    prices[1][11] = 1400;
    distances[1][12] = 1273;
    prices[1][12] = 1540;
    distances[1][13] = 1535;
    prices[1][13] = 1690;

    distances[2][3] = 268;
    prices[2][3] = 555;
    distances[2][4] = 384;
    prices[2][4] = 680;
    distances[2][5] = 1750;
    prices[2][5] = 5000;
    distances[2][6] = 912;
    prices[2][6] = 1230;
    distances[2][7] = 384;
    prices[2][7] = 680;
    distances[2][8] = 358;
    prices[2][8] = 600;
    distances[2][9] = 1410;
    prices[2][9] = 1600;
    distances[2][10] = 560;
    prices[2][10] = 945;
    distances[2][11] = 1774;
    prices[2][11] = 1865;
    distances[2][12] = 1359;
    prices[2][12] = 1610;
    distances[2][13] = 274;
    prices[2][13] = 555;

    distances[3][4] = 188;
    prices[3][4] = 505;
    distances[3][5] = 1920;
    prices[3][5] = 5000;
    distances[3][6] = 1169;
    prices[3][6] = 1425;
    distances[3][7] = 290;
    prices[3][7] = 505;
    distances[3][8] = 400;
    prices[3][8] = 570;
    distances[3][9] = 1628;
    prices[3][9] = 3320;
    distances[3][10] = 829;
    prices[3][10] = 1200;
    distances[3][11] = 2071;
    prices[3][11] = 2040;
    distances[3][12] = 1339;
    prices[3][12] = 1780;
    distances[3][13] = 349;
    prices[3][13] = 620;

    distances[4][5] = 1900;
    prices[4][5] = 4000;
    distances[4][6] = 1209;
    prices[4][6] = 1505;
    distances[4][7] = 96;
    prices[4][7] = 745;
    distances[4][8] = 273;
    prices[4][8] = 555;
    distances[4][9] = 1709;
    prices[4][9] = 1875;
    distances[4][10] = 944;
    prices[4][10] = 1320;
    distances[4][11] = 2087;
    prices[4][11] = 2060;
    distances[4][12] = 1759;
    prices[4][12] = 2255;
    distances[4][13] = 582;
    prices[4][13] = 730;

    distances[5][6] = 900;
    prices[5][6] = 3000;
    distances[5][7] = 2125;
    prices[5][7] = 5000;
    distances[5][8] = 2075;
    prices[5][8] = 5000;
    distances[5][9] = 375;
    prices[5][9] = 2000;
    distances[5][10] = 1725;
    prices[5][10] = 4000;
    distances[5][11] = 1375;
    prices[5][11] = 4000;
    distances[5][12] = 1175;
    prices[5][12] = 4000;
    distances[5][13] = 1875;
    prices[5][13] = 4000;

    distances[6][7] = 1154;
    prices[6][7] = 1425;
    distances[6][8] = 912;
    prices[6][8] = 1230;
    distances[6][9] = 531;
    prices[6][9] = 870;
    distances[6][10] = 1142;
    prices[6][10] = 1405;
    distances[6][11] = 910;
    prices[6][11] = 1345;
    distances[6][12] = 967;
    prices[6][12] = 1275;
    distances[6][13] = 1374;
    prices[6][13] = 1565;

    distances[7][8] = 242;
    prices[7][8] = 505;
    distances[7][9] = 1684;
    prices[7][9] = 1860;
    distances[7][10] = 927;
    prices[7][10] = 1285;
    distances[7][11] = 2087;
    prices[7][11] = 2060;
    distances[7][12] = 1789;
    prices[7][12] = 1865;
    distances[7][13] = 580;
    prices[7][13] = 940;

    distances[8][9] = 1443;
    prices[8][9] = 1620;
    distances[8][10] = 858;
    prices[8][10] = 1405;
    distances[8][11] = 1743;
    prices[8][11] = 1845;
    distances[8][12] = 1195;
    prices[8][12] = 1650;
    distances[8][13] = 584;
    prices[8][13] = 920;

    distances[9][10] = 1475;
    prices[9][10] = 1635;
    distances[9][11] = 998;
    prices[9][11] = 1365;
    distances[9][12] = 720;
    prices[9][12] = 1100;
    distances[9][13] = 1501;
    prices[9][13] = 1715;

    distances[10][11] = 1924;
    prices[10][11] = 2335;
    distances[10][12] = 736;
    prices[10][12] = 1120;
    distances[10][13] = 791;
    prices[10][13] = 1120;

    distances[10][11] = 1924;
    prices[10][11] = 2335;
    distances[10][12] = 736;
    prices[10][12] = 1120;
    distances[10][13] = 791;
    prices[10][13] = 1120;

    distances[11][12] = 1729;
    prices[11][12] = 1840;
    distances[11][13] = 1964;
    prices[11][13] = 1990;

    distances[12][13] = 1504;
    prices[12][13] = 1715;

    for (int i = 13; i >= 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            distances[i][j] = distances[j][i];
            prices[i][j] = prices[j][i];
        }
    }

    // for(int i=0;i<14;i++)
    // {
    //  for(int j=0;j<14;j++)
    //      printf("%d\n", distances[i][j]);
    // }
    for (int k = 0; k < 14; k++)
    {
        for (int i = 0; i < 14; i++)
        {
            for (int j = 0; j < 14; j++)
            {
                if (distances[i][j] > (distances[i][k] + distances[k][j]))
                {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
                if (prices[i][j] > (prices[i][k] + prices[k][j]))
                {
                    prices[i][j] = prices[i][k] + prices[k][j];
                }
            }
        }
    }

    for (int i = 0; i < 14; i++)
    {
        for (int j = i + 1; j < 14; j++)
        {
            printf("Shortest distance between %s(%s) & %s(%s) is: %d\n",
                   stations[i], stationcodes[i], stations[j], stationcodes[j], distances[i][j]);
            printf("Lowest price between %s(%s) & %s(%s) is: % d\n ",stations[i], stationcodes[i], stations[j], stationcodes[j], 
                   prices[i][j]);
            printf("\n");
        }
    }
    return 0;
}