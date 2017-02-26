#include <iostream>
#include <cmath>
#include "integration_rules_area.h"

int dunavant_degree(int p) {
    if (1 <= p && p <= 20) {
        return p;
    }
    else {
        printf("\n");
        printf("DUNAVANT_DEGREE - Fatal error!\n");
        printf("Illegal P = %d\n", p);
        exit(1);
    }
}

int dunavant_number_gp(int p) {
    int num_permutations;
    int* permutations;

    dunavant_permutation_data(p, &num_permutations, permutations);

    int number_gp = 0;
    for (int i = 0; i < num_permutations; i++) { number_gp = number_gp + permutations[i]; }

    delete[] permutations;

    return number_gp;
}

void dunavant_rule(int p, double x[], double y[], double weight[]) {
    double* l1;
    double* l2;
    double* l3;
    double* w;

    int num_permutations;
    int* permutations;

    dunavant_permutation_data(p, &num_permutations, permutations);
    dunavant_gp_data(p, l1, l2, l3, w);

    int gp_number = 0;
    for (int i = 0; i < num_permutations; i++) {
        if (permutations[i] == 1) {
            x[gp_number] = l1[i];
            y[gp_number] = l2[i];
            weight[gp_number] = w[i];

            gp_number = gp_number + 1;
        }
        else if (permutations[i] == 3) {
            x[gp_number] = l1[i];
            y[gp_number] = l2[i];
            weight[gp_number] = w[i];

            x[gp_number + 1] = l2[i];
            y[gp_number + 1] = l3[i];
            weight[gp_number + 1] = w[i];

            x[gp_number + 2] = l3[i];
            y[gp_number + 2] = l1[i];
            weight[gp_number + 2] = w[i];

            gp_number = gp_number + 3;
        }
        else if (permutations[i] == 6) {
            x[gp_number] = l1[i];
            y[gp_number] = l2[i];
            weight[gp_number] = w[i];

            x[gp_number + 1] = l2[i];
            y[gp_number + 1] = l3[i];
            weight[gp_number + 1] = w[i];

            x[gp_number + 2] = l3[i];
            y[gp_number + 2] = l1[i];
            weight[gp_number + 2] = w[i];

            x[gp_number + 3] = l2[i];
            y[gp_number + 3] = l1[i];
            weight[gp_number + 3] = w[i];

            x[gp_number + 4] = l3[i];
            y[gp_number + 4] = l2[i];
            weight[gp_number + 4] = w[i];

            x[gp_number + 5] = l1[i];
            y[gp_number + 5] = l3[i];
            weight[gp_number + 5] = w[i];

            gp_number = gp_number + 6;
        }
    }

    delete[] l1;
    delete[] l2;
    delete[] l3;
    delete[] w;

    delete[] permutations;
}

void dunavant_permutation_data(int p, int* num_permutations, int* &permutations) {
    if (p == 1) {
        *num_permutations = 1;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
    }
    else if (p == 2) {
        *num_permutations = 1;
        permutations = new int[*num_permutations];

        permutations[0] = 3;
    }
    else if (p == 3) {
        *num_permutations = 2;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
    }
    else if (p == 4) {
        *num_permutations = 2;
        permutations = new int[*num_permutations];

        permutations[0] = 3;
        permutations[1] = 3;
    }
    else if (p == 5) {
        *num_permutations = 3;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
    }
    else if (p == 6) {
        *num_permutations = 3;
        permutations = new int[*num_permutations];

        permutations[0] = 3;
        permutations[1] = 3;
        permutations[2] = 6;
    }
    else if (p == 7) {
        *num_permutations = 4;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 6;
    }
    else if (p == 8) {
        *num_permutations = 5;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 6;
    }
    else if (p == 9) {
        *num_permutations = 6;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 6;
    }
    else if (p == 10) {
        *num_permutations = 6;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 6;
        permutations[4] = 6;
        permutations[5] = 6;
    }
    else if (p == 11) {
        *num_permutations = 7;
        permutations = new int[*num_permutations];

        permutations[0] = 3;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 6;
        permutations[6] = 6;
    }
    else if (p == 12) {
        *num_permutations = 8;
        permutations = new int[*num_permutations];

        permutations[0] = 3;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 6;
        permutations[6] = 6;
        permutations[7] = 6;
    }
    else if (p == 13) {
        *num_permutations = 10;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 3;
        permutations[6] = 3;
        permutations[7] = 6;
        permutations[8] = 6;
        permutations[9] = 6;
    }
    else if (p == 14) {
        *num_permutations = 10;
        permutations = new int[*num_permutations];

        permutations[0] = 3;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 3;
        permutations[6] = 6;
        permutations[7] = 6;
        permutations[8] = 6;
        permutations[9] = 6;
    }
    else if (p == 15) {
        *num_permutations = 11;
        permutations = new int[*num_permutations];

        permutations[0] = 3;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 3;
        permutations[6] = 6;
        permutations[7] = 6;
        permutations[8] = 6;
        permutations[9] = 6;
        permutations[10] = 6;
    }
    else if (p == 16) {
        *num_permutations = 13;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 3;
        permutations[6] = 3;
        permutations[7] = 3;
        permutations[8] = 6;
        permutations[9] = 6;
        permutations[10] = 6;
        permutations[11] = 6;
        permutations[12] = 6;
    }
    else if (p == 17) {
        *num_permutations = 15;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 3;
        permutations[6] = 3;
        permutations[7] = 3;
        permutations[8] = 3;
        permutations[9] = 6;
        permutations[10] = 6;
        permutations[11] = 6;
        permutations[12] = 6;
        permutations[13] = 6;
        permutations[14] = 6;
    }
    else if (p == 18) {
        *num_permutations = 17;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 3;
        permutations[6] = 3;
        permutations[7] = 3;
        permutations[8] = 3;
        permutations[9] = 3;
        permutations[10] = 6;
        permutations[11] = 6;
        permutations[12] = 6;
        permutations[13] = 6;
        permutations[14] = 6;
        permutations[15] = 6;
        permutations[16] = 6;
    }
    else if (p == 19) {
        *num_permutations = 17;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 3;
        permutations[6] = 3;
        permutations[7] = 3;
        permutations[8] = 3;
        permutations[9] = 6;
        permutations[10] = 6;
        permutations[11] = 6;
        permutations[12] = 6;
        permutations[13] = 6;
        permutations[14] = 6;
        permutations[15] = 6;
        permutations[16] = 6;
    }
    else if (p == 20) {
        *num_permutations = 19;
        permutations = new int[*num_permutations];

        permutations[0] = 1;
        permutations[1] = 3;
        permutations[2] = 3;
        permutations[3] = 3;
        permutations[4] = 3;
        permutations[5] = 3;
        permutations[6] = 3;
        permutations[7] = 3;
        permutations[8] = 3;
        permutations[9] = 3;
        permutations[10] = 3;
        permutations[11] = 6;
        permutations[12] = 6;
        permutations[13] = 6;
        permutations[14] = 6;
        permutations[15] = 6;
        permutations[16] = 6;
        permutations[17] = 6;
        permutations[18] = 6;
    }
}

void dunavant_gp_data(int p, double* &l1, double* &l2, double* &l3, double* &w){
    if (p == 1) {
        l1 = new double[1];
        l2 = new double[1];
        l3 = new double[1];

        w = new double[1];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        w[0] = 1.000000000000000;
    }
    else if (p == 2) {
        l1 = new double[1];
        l2 = new double[1];
        l3 = new double[1];

        w = new double[1];

        l1[0] = 0.666666666666667;
        l2[0] = 0.166666666666667;
        l3[0] = 0.166666666666667;

        w[0] = 0.333333333333333;
    }
    else if (p == 3) {
        l1 = new double[2];
        l2 = new double[2];
        l3 = new double[2];

        w = new double[2];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.600000000000000;
        l2[1] = 0.200000000000000;
        l3[1] = 0.200000000000000;

        w[0] = -0.562500000000000;

        w[1] = 0.520833333333333;
    }
    else if (p == 4) {
        l1 = new double[2];
        l2 = new double[2];
        l3 = new double[2];

        w = new double[2];

        l1[0] = 0.108103018168070;
        l2[0] = 0.445948490915965;
        l3[0] = 0.445948490915965;

        l1[1] = 0.816847572980459;
        l2[1] = 0.091576213509771;
        l3[1] = 0.091576213509771;

        w[0] = 0.223381589678011;

        w[1] = 0.109951743655322;
    }
    else if (p == 5) {
        l1 = new double[3];
        l2 = new double[3];
        l3 = new double[3];

        w = new double[3];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.059715871789770;
        l2[1] = 0.470142064105115;
        l3[1] = 0.470142064105115;

        l1[2] = 0.797426985353087;
        l2[2] = 0.101286507323456;
        l3[2] = 0.101286507323456;

        w[0] = 0.225000000000000;

        w[1] = 0.132394152788506;

        w[2] = 0.125939180544827;
    }
    else if (p == 6) {
        l1 = new double[3];
        l2 = new double[3];
        l3 = new double[3];

        w = new double[3];

        l1[0] = 0.501426509658179;
        l2[0] = 0.249286745170910;
        l3[0] = 0.249286745170910;

        l1[1] = 0.873821971016996;
        l2[1] = 0.063089014491502;
        l3[1] = 0.063089014491502;

        l1[2] = 0.053145049844817;
        l2[2] = 0.310352451033784;
        l3[2] = 0.636502499121399;

        w[0] = 0.116786275726379;

        w[1] = 0.050844906370207;

        w[2] = 0.082851075618374;
    }
    else if (p == 7) {
        l1 = new double[4];
        l2 = new double[4];
        l3 = new double[4];

        w = new double[4];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.479308067841920;
        l2[1] = 0.260345966079040;
        l3[1] = 0.260345966079040;

        l1[2] = 0.869739794195568;
        l2[2] = 0.065130102902216;
        l3[2] = 0.065130102902216;

        l1[3] = 0.048690315425316;
        l2[3] = 0.312865496004874;
        l3[3] = 0.638444188569810;

        w[0] = -0.149570044467682;

        w[1] = 0.175615257433208;

        w[2] = 0.053347235608838;

        w[3] = 0.077113760890257;
    }
    else if (p == 8) {
        l1 = new double[5];
        l2 = new double[5];
        l3 = new double[5];

        w = new double[5];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.081414823414554;
        l2[1] = 0.459292588292723;
        l3[1] = 0.459292588292723;

        l1[2] = 0.658861384496480;
        l2[2] = 0.170569307751760;
        l3[2] = 0.170569307751760;

        l1[3] = 0.898905543365938;
        l2[3] = 0.050547228317031;
        l3[3] = 0.050547228317031;

        l1[4] = 0.008394777409958;
        l2[4] = 0.263112829634638;
        l3[4] = 0.728492392955404;

        w[0] = 0.144315607677787;

        w[1] = 0.095091634267285;

        w[2] = 0.103217370534718;

        w[3] = 0.032458497623198;

        w[4] = 0.027230314174435;
    }
    else if (p == 9) {
        l1 = new double[6];
        l2 = new double[6];
        l3 = new double[6];

        w = new double[6];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.020634961602525;
        l2[1] = 0.489682519198738;
        l3[1] = 0.489682519198738;

        l1[2] = 0.125820817014127;
        l2[2] = 0.437089591492937;
        l3[2] = 0.437089591492937;

        l1[3] = 0.623592928761935;
        l2[3] = 0.188203535619033;
        l3[3] = 0.188203535619033;

        l1[4] = 0.910540973211095;
        l2[4] = 0.044729513394453;
        l3[4] = 0.044729513394453;

        l1[5] = 0.036838412054736;
        l2[5] = 0.221962989160766;
        l3[5] = 0.741198598784498;

        w[0] = 0.097135796282799;

        w[1] = 0.031334700227139;

        w[2] = 0.077827541004774;

        w[3] = 0.079647738927210;

        w[4] = 0.025577675658698;

        w[5] = 0.043283539377289;
    }
    else if (p == 10) {
        l1 = new double[6];
        l2 = new double[6];
        l3 = new double[6];

        w = new double[6];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.028844733232685;
        l2[1] = 0.485577633383657;
        l3[1] = 0.485577633383657;

        l1[2] = 0.781036849029926;
        l2[2] = 0.109481575485037;
        l3[2] = 0.109481575485037;

        l1[3] = 0.141707219414880;
        l2[3] = 0.307939838764121;
        l3[3] = 0.550352941820999;

        l1[4] = 0.025003534762686;
        l2[4] = 0.246672560639903;
        l3[4] = 0.728323904597411;

        l1[5] = 0.009540815400299;
        l2[5] = 0.066803251012200;
        l3[5] = 0.923655933587500;

        w[0] = 0.090817990382754;

        w[1] = 0.036725957756467;

        w[2] = 0.045321059435528;

        w[3] = 0.072757916845420;

        w[4] = 0.028327242531057;

        w[5] = 0.009421666963733;
    }
    else if (p == 11) {
        l1 = new double[7];
        l2 = new double[7];
        l3 = new double[7];

        w = new double[7];

        l1[0] = -0.069222096541517;
        l2[0] = 0.534611048270758;
        l3[0] = 0.534611048270758;

        l1[1] = 0.202061394068290;
        l2[1] = 0.398969302965855;
        l3[1] = 0.398969302965855;

        l1[2] = 0.593380199137435;
        l2[2] = 0.203309900431282;
        l3[2] = 0.203309900431282;

        l1[3] = 0.761298175434837;
        l2[3] = 0.119350912282581;
        l3[3] = 0.119350912282581;

        l1[4] = 0.935270103777448;
        l2[4] = 0.032364948111276;
        l3[4] = 0.032364948111276;

        l1[5] = 0.050178138310495;
        l2[5] = 0.356620648261293;
        l3[5] = 0.593201213428213;

        l1[6] = 0.021022016536166;
        l2[6] = 0.171488980304042;
        l3[6] = 0.807489003159792;

        w[0] = 0.000927006328961;

        w[1] = 0.077149534914813;

        w[2] = 0.059322977380774;

        w[3] = 0.036184540503418;

        w[4] = 0.013659731002678;

        w[5] = 0.052337111962204;

        w[6] = 0.020707659639141;
    }
    else if (p == 12) {
        l1 = new double[8];
        l2 = new double[8];
        l3 = new double[8];

        w = new double[8];

        l1[0] = 0.02356522045239;
        l2[0] = 0.488217389773805;
        l3[0] = 0.488217389773805;

        l1[1] = 0.120551215411079;
        l2[1] = 0.43972439229446;
        l3[1] = 0.43972439229446;

        l1[2] = 0.457579229975768;
        l2[2] = 0.271210385012116;
        l3[2] = 0.271210385012116;

        l1[3] = 0.744847708916828;
        l2[3] = 0.127576145541586;
        l3[3] = 0.127576145541586;

        l1[4] = 0.957365299093579;
        l2[4] = 0.02131735045321;
        l3[4] = 0.02131735045321;

        l1[5] = 0.115343494534698;
        l2[5] = 0.275713269685514;
        l3[5] = 0.608943235779788;

        l1[6] = 0.022838332222257;
        l2[6] = 0.28132558098994;
        l3[6] = 0.695836086787803;

        l1[7] = 0.02573405054833;
        l2[7] = 0.116251915907597;
        l3[7] = 0.858014033544073;

        w[0] = 0.025731066440455;

        w[1] = 0.043692544538038;

        w[2] = 0.062858224217885;

        w[3] = 0.034796112930709;

        w[4] = 0.006166261051559;

        w[5] = 0.040371557766381;

        w[6] = 0.022356773202303;

        w[7] = 0.017316231108659;
    }
    else if (p == 13) {
        l1 = new double[10];
        l2 = new double[10];
        l3 = new double[10];

        w = new double[10];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.009903630120591;
        l2[1] = 0.495048184939705;
        l3[1] = 0.495048184939705;

        l1[2] = 0.062566729780852;
        l2[2] = 0.468716635109574;
        l3[2] = 0.468716635109574;

        l1[3] = 0.170957326397447;
        l2[3] = 0.414521336801277;
        l3[3] = 0.414521336801277;

        l1[4] = 0.541200855914337;
        l2[4] = 0.229399572042831;
        l3[4] = 0.229399572042831;

        l1[5] = 0.77115100960734;
        l2[5] = 0.11442449519633;
        l3[5] = 0.11442449519633;

        l1[6] = 0.950377217273082;
        l2[6] = 0.024811391363459;
        l3[6] = 0.024811391363459;

        l1[7] = 0.094853828379579;
        l2[7] = 0.268794997058761;
        l3[7] = 0.63635117456166;

        l1[8] = 0.018100773278807;
        l2[8] = 0.291730066734288;
        l3[8] = 0.690169159986905;

        l1[9] = 0.02223307667409;
        l2[9] = 0.126357385491669;
        l3[9] = 0.851409537834241;

        w[0] = 0.052520923400802;

        w[1] = 0.01128014520933;

        w[2] = 0.031423518362454;

        w[3] = 0.047072502504194;

        w[4] = 0.047363586536355;

        w[5] = 0.031167529045794;

        w[6] = 0.007975771465074;

        w[7] = 0.036848402728732;

        w[8] = 0.017401463303822;

        w[9] = 0.015521786839045;
    }
    else if (p == 14) {
        l1 = new double[10];
        l2 = new double[10];
        l3 = new double[10];

        w = new double[10];

        l1[0] = 0.022072179275643;
        l2[0] = 0.488963910362179;
        l3[0] = 0.488963910362179;

        l1[1] = 0.164710561319092;
        l2[1] = 0.417644719340454;
        l3[1] = 0.417644719340454;

        l1[2] = 0.453044943382323;
        l2[2] = 0.273477528308839;
        l3[2] = 0.273477528308839;

        l1[3] = 0.645588935174913;
        l2[3] = 0.177205532412543;
        l3[3] = 0.177205532412543;

        l1[4] = 0.876400233818255;
        l2[4] = 0.061799883090873;
        l3[4] = 0.061799883090873;

        l1[5] = 0.961218077502598;
        l2[5] = 0.019390961248701;
        l3[5] = 0.019390961248701;

        l1[6] = 0.057124757403648;
        l2[6] = 0.172266687821356;
        l3[6] = 0.770608554774996;

        l1[7] = 0.092916249356972;
        l2[7] = 0.336861459796345;
        l3[7] = 0.570222290846683;

        l1[8] = 0.014646950055654;
        l2[8] = 0.298372882136258;
        l3[8] = 0.686980167808088;

        l1[9] = 0.001268330932872;
        l2[9] = 0.118974497696957;
        l3[9] = 0.879757171370171;

        w[0] = 0.021883581369429;

        w[1] = 0.032788353544125;

        w[2] = 0.051774104507292;

        w[3] = 0.042162588736993;

        w[4] = 0.014433699669777;

        w[5] = 0.0049234036024;

        w[6] = 0.024665753212564;

        w[7] = 0.038571510787061;

        w[8] = 0.014436308113534;

        w[9] = 0.005010228838501;
    }
    else if (p == 15) {
        l1 = new double[11];
        l2 = new double[11];
        l3 = new double[11];

        w = new double[11];

        l1[0] = -0.013945833716486;
        l2[0] = 0.506972916858243;
        l3[0] = 0.506972916858243;

        l1[1] = 0.137187291433955;
        l2[1] = 0.431406354283023;
        l3[1] = 0.431406354283023;

        l1[2] = 0.444612710305711;
        l2[2] = 0.277693644847144;
        l3[2] = 0.277693644847144;

        l1[3] = 0.747070217917492;
        l2[3] = 0.126464891041254;
        l3[3] = 0.126464891041254;

        l1[4] = 0.858383228050628;
        l2[4] = 0.070808385974686;
        l3[4] = 0.070808385974686;

        l1[5] = 0.962069659517853;
        l2[5] = 0.018965170241073;
        l3[5] = 0.018965170241073;

        l1[6] = 0.133734161966621;
        l2[6] = 0.261311371140087;
        l3[6] = 0.604954466893291;

        l1[7] = 0.036366677396917;
        l2[7] = 0.388046767090269;
        l3[7] = 0.575586555512814;

        l1[8] = -0.010174883126571;
        l2[8] = 0.285712220049916;
        l3[8] = 0.724462663076655;

        l1[9] = 0.036843869875878;
        l2[9] = 0.215599664072284;
        l3[9] = 0.747556466051838;

        l1[10] = 0.012459809331199;
        l2[10] = 0.103575616576386;
        l3[10] = 0.883964574092416;

        w[0] = 0.001916875642849;

        w[1] = 0.044249027271145;

        w[2] = 0.051186548718852;

        w[3] = 0.023687735870688;

        w[4] = 0.013289775690021;

        w[5] = 0.004748916608192;

        w[6] = 0.038550072599593;

        w[7] = 0.027215814320624;

        w[8] = 0.002182077366797;

        w[9] = 0.021505319847731;

        w[10] = 0.007673942631049;
    }
    else if (p == 16) {
        l1 = new double[13];
        l2 = new double[13];
        l3 = new double[13];

        w = new double[13];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.005238916103123;
        l2[1] = 0.497380541948438;
        l3[1] = 0.497380541948438;

        l1[2] = 0.173061122901295;
        l2[2] = 0.413469438549352;
        l3[2] = 0.413469438549352;

        l1[3] = 0.059082801866017;
        l2[3] = 0.470458599066991;
        l3[3] = 0.470458599066991;

        l1[4] = 0.518892500060958;
        l2[4] = 0.240553749969521;
        l3[4] = 0.240553749969521;

        l1[5] = 0.704068411554854;
        l2[5] = 0.147965794222573;
        l3[5] = 0.147965794222573;

        l1[6] = 0.849069624685052;
        l2[6] = 0.075465187657474;
        l3[6] = 0.075465187657474;

        l1[7] = 0.96680719475395;
        l2[7] = 0.016596402623025;
        l3[7] = 0.016596402623025;

        l1[8] = 0.103575692245252;
        l2[8] = 0.296555596579887;
        l3[8] = 0.599868711174861;

        l1[9] = 0.020083411655416;
        l2[9] = 0.337723063403079;
        l3[9] = 0.642193524941505;

        l1[10] = -0.004341002614139;
        l2[10] = 0.204748281642812;
        l3[10] = 0.799592720971327;

        l1[11] = 0.04194178646801;
        l2[11] = 0.189358492130623;
        l3[11] = 0.768699721401368;

        l1[12] = 0.014317320230681;
        l2[12] = 0.085283615682657;
        l3[12] = 0.900399064086661;

        w[0] = 0.046875697427642;

        w[1] = 0.006405878578585;

        w[2] = 0.041710296739387;

        w[3] = 0.026891484250064;

        w[4] = 0.04213252276165;

        w[5] = 0.030000266842773;

        w[6] = 0.014200098925024;

        w[7] = 0.003582462351273;

        w[8] = 0.032773147460627;

        w[9] = 0.015298306248441;

        w[10] = 0.002386244192839;

        w[11] = 0.019084792755899;

        w[12] = 0.006850054546542;
    }
    else if (p == 17) {
        l1 = new double[15];
        l2 = new double[15];
        l3 = new double[15];

        w = new double[15];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.005658918886452;
        l2[1] = 0.497170540556774;
        l3[1] = 0.497170540556774;

        l1[2] = 0.035647354750751;
        l2[2] = 0.482176322624625;
        l3[2] = 0.482176322624625;

        l1[3] = 0.099520061958437;
        l2[3] = 0.450239969020782;
        l3[3] = 0.450239969020782;

        l1[4] = 0.199467521245206;
        l2[4] = 0.400266239377397;
        l3[4] = 0.400266239377397;

        l1[5] = 0.495717464058095;
        l2[5] = 0.252141267970953;
        l3[5] = 0.252141267970953;

        l1[6] = 0.675905990683077;
        l2[6] = 0.162047004658461;
        l3[6] = 0.162047004658461;

        l1[7] = 0.848248235478508;
        l2[7] = 0.075875882260746;
        l3[7] = 0.075875882260746;

        l1[8] = 0.968690546064356;
        l2[8] = 0.015654726967822;
        l3[8] = 0.015654726967822;

        l1[9] = 0.010186928826919;
        l2[9] = 0.334319867363658;
        l3[9] = 0.655493203809423;

        l1[10] = 0.135440871671036;
        l2[10] = 0.292221537796944;
        l3[10] = 0.57233759053202;

        l1[11] = 0.054423924290583;
        l2[11] = 0.31957488542319;
        l3[11] = 0.626001190286228;

        l1[12] = 0.012868560833637;
        l2[12] = 0.190704224192292;
        l3[12] = 0.796427214974071;

        l1[13] = 0.067165782413524;
        l2[13] = 0.180483211648746;
        l3[13] = 0.752351005937729;

        l1[14] = 0.014663182224828;
        l2[14] = 0.080711313679564;
        l3[14] = 0.904625504095608;

        w[0] = 0.033437199290803;

        w[1] = 0.005093415440507;

        w[2] = 0.014670864527638;

        w[3] = 0.024350878353672;

        w[4] = 0.031107550868969;

        w[5] = 0.03125711121862;

        w[6] = 0.024815654339665;

        w[7] = 0.014056073070557;

        w[8] = 0.003194676173779;

        w[9] = 0.008119655318993;

        w[10] = 0.026805742283163;

        w[11] = 0.018459993210822;

        w[12] = 0.008476868534328;

        w[13] = 0.018292796770025;

        w[14] = 0.006665632004165;
    }
    else if (p == 18) {
        l1 = new double[17];
        l2 = new double[17];
        l3 = new double[17];

        w = new double[17];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.013310382738157;
        l2[1] = 0.493344808630921;
        l3[1] = 0.493344808630921;

        l1[2] = 0.061578811516086;
        l2[2] = 0.469210594241957;
        l3[2] = 0.469210594241957;

        l1[3] = 0.127437208225989;
        l2[3] = 0.436281395887006;
        l3[3] = 0.436281395887006;

        l1[4] = 0.210307658653168;
        l2[4] = 0.394846170673416;
        l3[4] = 0.394846170673416;

        l1[5] = 0.500410862393686;
        l2[5] = 0.249794568803157;
        l3[5] = 0.249794568803157;

        l1[6] = 0.677135612512315;
        l2[6] = 0.161432193743843;
        l3[6] = 0.161432193743843;

        l1[7] = 0.846803545029257;
        l2[7] = 0.076598227485371;
        l3[7] = 0.076598227485371;

        l1[8] = 0.9514951212931;
        l2[8] = 0.02425243935345;
        l3[8] = 0.02425243935345;

        l1[9] = 0.913707265566071;
        l2[9] = 0.043146367216965;
        l3[9] = 0.043146367216965;

        l1[10] = 0.00843053620242;
        l2[10] = 0.358911494940944;
        l3[10] = 0.632657968856636;

        l1[11] = 0.131186551737188;
        l2[11] = 0.294402476751957;
        l3[11] = 0.574410971510855;

        l1[12] = 0.050203151565675;
        l2[12] = 0.325017801641814;
        l3[12] = 0.624779046792512;

        l1[13] = 0.066329263810916;
        l2[13] = 0.184737559666046;
        l3[13] = 0.748933176523037;

        l1[14] = 0.011996194566236;
        l2[14] = 0.218796800013321;
        l3[14] = 0.769207005420443;

        l1[15] = 0.014858100590125;
        l2[15] = 0.101179597136408;
        l3[15] = 0.883962302273467;

        l1[16] = -0.035222015287949;
        l2[16] = 0.020874755282586;
        l3[16] = 1.01434726000536;

        w[0] = 0.030809939937647;

        w[1] = 0.009072436679404;

        w[2] = 0.018761316939594;

        w[3] = 0.019441097985477;

        w[4] = 0.02775394861081;

        w[5] = 0.032256225351457;

        w[6] = 0.025074032616922;

        w[7] = 0.015271927971832;

        w[8] = 0.006793922022963;

        w[9] = -0.00222309872992;

        w[10] = 0.006331914076406;

        w[11] = 0.027257538049138;

        w[12] = 0.017676785649465;

        w[13] = 0.01837948463807;

        w[14] = 0.008104732808192;

        w[15] = 0.007634129070725;

        w[16] = 0.000046187660794;
    }
    else if (p == 19) {
        l1 = new double[17];
        l2 = new double[17];
        l3 = new double[17];

        w = new double[17];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = 0.020780025853987;
        l2[1] = 0.489609987073006;
        l3[1] = 0.489609987073006;

        l1[2] = 0.090926214604215;
        l2[2] = 0.454536892697893;
        l3[2] = 0.454536892697893;

        l1[3] = 0.197166638701138;
        l2[3] = 0.401416680649431;
        l3[3] = 0.401416680649431;

        l1[4] = 0.488896691193805;
        l2[4] = 0.255551654403098;
        l3[4] = 0.255551654403098;

        l1[5] = 0.645844115695741;
        l2[5] = 0.17707794215213;
        l3[5] = 0.17707794215213;

        l1[6] = 0.779877893544096;
        l2[6] = 0.110061053227952;
        l3[6] = 0.110061053227952;

        l1[7] = 0.888942751496321;
        l2[7] = 0.05552862425184;
        l3[7] = 0.05552862425184;

        l1[8] = 0.974756272445543;
        l2[8] = 0.012621863777229;
        l3[8] = 0.012621863777229;

        l1[9] = 0.003611417848412;
        l2[9] = 0.395754787356943;
        l3[9] = 0.600633794794645;

        l1[10] = 0.13446675453078;
        l2[10] = 0.307929983880436;
        l3[10] = 0.557603261588784;

        l1[11] = 0.014446025776115;
        l2[11] = 0.26456694840652;
        l3[11] = 0.720987025817365;

        l1[12] = 0.046933578838178;
        l2[12] = 0.358539352205951;
        l3[12] = 0.594527068955871;

        l1[13] = 0.002861120350567;
        l2[13] = 0.157807405968595;
        l3[13] = 0.839331473680839;

        l1[14] = 0.223861424097916;
        l2[14] = 0.075050596975911;
        l3[14] = 0.701087978926173;

        l1[15] = 0.03464707481676;
        l2[15] = 0.142421601113383;
        l3[15] = 0.822931324069857;

        l1[16] = 0.010161119296278;
        l2[16] = 0.065494628082938;
        l3[16] = 0.924344252620784;

        w[0] = 0.032906331388919;

        w[1] = 0.010330731891272;

        w[2] = 0.022387247263016;

        w[3] = 0.030266125869468;

        w[4] = 0.030490967802198;

        w[5] = 0.024159212741641;

        w[6] = 0.016050803586801;

        w[7] = 0.008084580261784;

        w[8] = 0.002079362027485;

        w[9] = 0.003884876904981;

        w[10] = 0.025574160612022;

        w[11] = 0.008880903573338;

        w[12] = 0.016124546761731;

        w[13] = 0.002491941817491;

        w[14] = 0.018242840118951;

        w[15] = 0.010258563736199;

        w[16] = 0.003799928855302;
    }
    else if (p == 20) {
        l1 = new double[19];
        l2 = new double[19];
        l3 = new double[19];

        w = new double[19];

        l1[0] = 0.333333333333333;
        l2[0] = 0.333333333333333;
        l3[0] = 0.333333333333333;

        l1[1] = -0.0019009287044;
        l2[1] = 0.5009504643522;
        l3[1] = 0.5009504643522;

        l1[2] = 0.023574084130543;
        l2[2] = 0.488212957934729;
        l3[2] = 0.488212957934729;

        l1[3] = 0.089726636099435;
        l2[3] = 0.455136681950283;
        l3[3] = 0.455136681950283;

        l1[4] = 0.196007481363421;
        l2[4] = 0.401996259318289;
        l3[4] = 0.401996259318289;

        l1[5] = 0.488214180481157;
        l2[5] = 0.255892909759421;
        l3[5] = 0.255892909759421;

        l1[6] = 0.647023488009788;
        l2[6] = 0.176488255995106;
        l3[6] = 0.176488255995106;

        l1[7] = 0.791658289326483;
        l2[7] = 0.104170855336758;
        l3[7] = 0.104170855336758;

        l1[8] = 0.89386207231814;
        l2[8] = 0.05306896384093;
        l3[8] = 0.05306896384093;

        l1[9] = 0.916762569607942;
        l2[9] = 0.041618715196029;
        l3[9] = 0.041618715196029;

        l1[10] = 0.976836157186356;
        l2[10] = 0.011581921406822;
        l3[10] = 0.011581921406822;

        l1[11] = 0.048741583664839;
        l2[11] = 0.344855770229001;
        l3[11] = 0.60640264610616;

        l1[12] = 0.006314115948605;
        l2[12] = 0.377843269594854;
        l3[12] = 0.615842614456541;

        l1[13] = 0.134316520547348;
        l2[13] = 0.306635479062357;
        l3[13] = 0.559048000390295;

        l1[14] = 0.013973893962392;
        l2[14] = 0.249419362774742;
        l3[14] = 0.736606743262866;

        l1[15] = 0.075549132909764;
        l2[15] = 0.212775724802802;
        l3[15] = 0.711675142287434;

        l1[16] = -0.008368153208227;
        l2[16] = 0.146965436053239;
        l3[16] = 0.861402717154987;

        l1[17] = 0.026686063258714;
        l2[17] = 0.137726978828923;
        l3[17] = 0.835586957912363;

        l1[18] = 0.010547719294141;
        l2[18] = 0.059696109149007;
        l3[18] = 0.929756171556853;

        w[0] = 0.033057055541624;

        w[1] = 0.000867019185663;

        w[2] = 0.011660052716448;

        w[3] = 0.022876936356421;

        w[4] = 0.030448982673938;

        w[5] = 0.030624891725355;

        w[6] = 0.0243680576768;

        w[7] = 0.015997432032024;

        w[8] = 0.007698301815602;

        w[9] = -0.000632060497488;

        w[10] = 0.001751134301193;

        w[11] = 0.016465839189576;

        w[12] = 0.004839033540485;

        w[13] = 0.02580490653465;

        w[14] = 0.008471091054441;

        w[15] = 0.01835491410628;

        w[16] = 0.000704404677908;

        w[17] = 0.010112684927462;

        w[18] = 0.00357390938595;
    }
}

void dunavant_rule_test(int p, int number_gp, double z1[], double z2[], double w[]) {
    double exact_integration = 1 / ((double)p + 1)*((1 - pow(-1.0, p)) / ((double)p + 2) + 2 * pow(-1.0, p)); // S(x^p)dxdy over triangle

    double num_integration = 0;
    for (int i = 0; i < number_gp; i++) { num_integration = num_integration + pow(z1[i], p)*w[i]; }

    double err = abs((num_integration - exact_integration) / exact_integration);

    if (err < pow(10.0, -10.0)) {
        printf("\n");
        printf("DUNAVANT_RULE - Test success!\n");
        printf("err = %e\n", err);
    }
    else {
        printf("\n");
        printf("DUNAVANT_RULE - Test fail!\n");
        printf("err = %e\n", err);
        exit(1);
    }
}