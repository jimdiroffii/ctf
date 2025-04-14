// google-beginnerquest2023.cpp
// James Diroff II
// @jimdiroffii
// Jan 02, 2024

#include "p0000.hpp"
#include "p1837.hpp"

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>

void solve0000() {
  {
    std::string cipher0 = "Naljnl, Pnrfne jnf n fxvyyrq pbzzhavpngbe, naq ur hfrq n inevrgl bs zrgubqf gb xrrc uvf zrffntrf frperg sebz uvf rarzvrf. Bar bs gurfr zrgubqf jnf gur Pnrfne pvcure, n fvzcyr grpuavdhr gb boshfpngr pbzzhavpngvbaf. SYNT{ebgngr_gung_nycunorg}";
    std::cout << "cipher: " << cipher0 << "\n";
    std::cout << "text:" << caesar(cipher0, 13) << "\n\n";
    //brutus(cipher0);
  }

  /* {
    std::string cipher1 = "Vhi Nixgnije tkplwr zu a tglpcltzasgtmu sldsxatlvisf czrhij. Ik ks e eoig sshhzutmuakgd zwrjkor gf kje Gsejcr gapygr, azitj uwws r uirylv uhmxt mclyw tf gngjygv tlw eevivw mvuseye. WNAK{yek_xikyy_nktl_at}";
    std::cout << "cipher: " << cipher1 << "\n";
    std::vector<int> key = { 24, 0, 22, 8, 0, 9 };
    std::cout << seqCaesar(cipher1, key) << "\n\n";
  }*/

  /* {
    std::string cipher2 = "PDV KLRBC IOEXQ AEY TLGMF EJVO PDV NSWH ZEU.\nPDRF PVYP RF S MSQUOSG, XDRBD GVSQF PDSP RP BEQPSRQF SNN 26 NVPPVOF EA PDV VQUNRFD SNMDSIVP.PDRF GSCVF RP RZVSN AEO AOVKLVQBH SQSNHFRF, SF PDV BOHMPSQSNHFP BSQ BEGMSOV PDV AOVKLVQBH EA NVPPVOF RQ PDV BRMDVOPVYP PE PDV CQEXQ AOVKLVQBH EA NVPPVOF RQ PDV VQUNRFD NSQULSUV.\nAEO VYSGMNV, PDV GEFP BEGGEQ NVPPVO RQ PDV VQUNRFD NSQULSUV RF V.RA PDV GEFP BEGGEQ NVPPVO RQ PDV BRMDVOPVYP RF Y, PDVQ PDV BOHMPSQSNHFP BSQ SFFLGV PDSP Y RF NRCVNH PE IV S FLIFPRPLPREQ AEO V.\nEPDVO BEGGEQ NVPPVOF RQ PDV VQUNRFD NSQULSUV RQBNLZV P, S, E, R, Q, F, SQZ D.PDV BOHMPSQSNHFP BSQ LFV PDRF RQAEOGSPREQ PE GSCV VZLBSPVZ ULVFFVF SIELP PDV EPDVO FLIFPRPLPREQF RQ PDV BRMDVOPVYP.\nANSU{ QEX_RJV_NVSOQVZ_GH_SIBF }";
    std::cout << "cipher: " << cipher2 << "\n";
    std::map<char, char> key{};
    key['A'] = 'F';
    key['B'] = 'C';
    key['C'] = 'K';
    key['D'] = 'H';
    key['E'] = 'O';
    key['F'] = 'S';
    key['G'] = 'M';
    key['H'] = 'Y';
    key['I'] = 'B';
    key['J'] = 'V';
    key['K'] = 'Q';
    key['L'] = 'U';
    key['M'] = 'P';
    key['N'] = 'L';
    key['O'] = 'R';
    key['P'] = 'T';
    key['Q'] = 'N';
    key['R'] = 'I';
    key['S'] = 'A';
    key['T'] = 'J';
    key['U'] = 'G';
    key['V'] = 'E';
    key['W'] = 'Z';
    key['X'] = 'W';
    key['Y'] = 'X';
    key['Z'] = 'D';
    std::cout << "text: " << mapCaesar(cipher2, key) << '\n';
  }*/

  /* {
    std::string cipher3 = "rs␣r␣enigm␣_aierhe␣i␣gluucsclhetersnti␣a␣rla␣t␣riayrgpetai␣diu␣Fawhiho}sipatfy␣ihr␣a␣rfa␣pes␣etohwrea␣octtonee␣eihetTpxcdeghi␣ro␣ped␣yGaledemXToneepetlhtseghectnatanst␣ripctiharaics␣foarscee␣ebrn␣te␣doemrr␣c__ltcsaicsa␣coo␣wbrn␣_aranmeibti,haarhra,sipklti␣ci.ctst␣a␣lxtcnaenlkLeoakelXpohry␣patakrntd␣cilxsU␣inehe␣cwthers␣rpo␣narahhtr␣aienlsrtrr␣o.{rd___nXnti␣_ornrtoyrgoors␣te.ksip␣_crs␣_c␣pohelhgctn␣ie␣erntatecg␣teeeAsuvesuX";
    transpositionIteration(cipher3); // iterate to six columns to solve the puzzle
  }*/



  /*std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int i = 1;
  for (auto ch : alphabet) {
    std::cout << std::left << std::setw(3) << i++ << ": " << ch << '\n';
  }*/
}

void solve1837() {
  {
    std::string code = "..-. .-. --- --/-.   .   .--/-.-- --- .-. -.-/.. .   ..   -   .. ../..- ... .-/-   . ./.-.. --- -. -.. --- -./..-   -.   ..   -   .   -../-.- .. -. --. -.. --- --/. ..   .   ..-.   ..-   .   ...   -/- ---/.   .-..   -   . ..   .-   .. .   -/..-. .-.. .- --./{-   . ..   ....-   -.   ---   ....-   -   â¸º   ....-   -.   -   ..   .. .}/--- -./. .   . ..   -..   .   . ../--- ..-./...   .   -.   -..   .   . ../--. --- --- --. .-.. ./.. .   -   .-.";
    std::string flag = "..-. .-.. .- --./{-   . ..   ....-   -.   ---   ....-   -   â¸º   ....-   -.   -   ..   .. .}";
    //std::cout << decodeMorse(cipher) << '\n';
    //decodeMorse(cipher);
    std::cout << decodeMorse2(flag);
  }
}

int main()
{
  //solve0000();
  solve1837();
}

