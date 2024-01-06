/***
 * Google CTF - Beginner's Quest
 * Main Driver Program
 *
 * By: jimdiroffii
 *
 * CTF: https://capturetheflag.withgoogle.com/beginners-quest
 *
 * A collection of functions and solutions to the Beginner's Quest problems
 */

#include "P0000.h"
#include <iostream>

int main()
{
  /***
   * Problem Set 0000
   * Caesar (and related) Ciphers and Transpositions
   */
  /*
  {
    // 0000 Challenge 0 - Standard Caesar with shift value 13
    {
      std::string cipher0 =
        "Naljnl, Pnrfne jnf n fxvyyrq pbzzhavpngbe, naq ur hfrq n inevrgl bs zrg"
        "ubqf gb xrrc uvf zrffntrf frperg sebz uvf rarzvrf. Bar bs gurfr zrgubqf"
        " jnf gur Pnrfne pvcure, n fvzcyr grpuavdhr gb boshfpngr pbzzhavpngvbaf."
        " SYNT{ebgngr_gung_nycunorg}";
      std::cout << "cipher: " << cipher0 << "\n\n";
      std::cout << "plaintext: " << caesar(cipher0, 13) << "\n\n";
    }

    // 0000 Challenge 1 - Caesar with a keyed shift sequence based on `caesar`
    {
      std::string cipher1 =
        "Vhi Nixgnije tkplwr zu a tglpcltzasgtmu sldsxatlvisf czrhij. Ik ks e eo"
        "ig sshhzutmuakgd zwrjkor gf kje Gsejcr gapygr, azitj uwws r uirylv uhmx"
        "t mclyw tf gngjygv tlw eevivw mvuseye. WNAK{yek_xikyy_nktl_at}";
      std::cout << "cipher: " << cipher1 << "\n\n";
      std::vector<int> key = { 24, 0, 22, 8, 0, 9 };
      std::cout << "plaintext: " << seqCaesar(cipher1, key) << "\n\n";
    }

    // 0000 Challenge 2 - Remapped alphabet, solved iteratively using frequency
    {
      std::string cipher2 =
        "PDV KLRBC IOEXQ AEY TLGMF EJVO PDV NSWH ZEU.\nPDRF PVYP RF S MSQUOSG, X"
        "DRBD GVSQF PDSP RP BEQPSRQF SNN 26 NVPPVOF EA PDV VQUNRFD SNMDSIVP.PDRF"
        " GSCVF RP RZVSN AEO AOVKLVQBH SQSNHFRF, SF PDV BOHMPSQSNHFP BSQ BEGMSOV"
        " PDV AOVKLVQBH EA NVPPVOF RQ PDV BRMDVOPVYP PE PDV CQEXQ AOVKLVQBH EA N"
        "VPPVOF RQ PDV VQUNRFD NSQULSUV.\nAEO VYSGMNV, PDV GEFP BEGGEQ NVPPVO RQ"
        " PDV VQUNRFD NSQULSUV RF V.RA PDV GEFP BEGGEQ NVPPVO RQ PDV BRMDVOPVYP "
        "RF Y, PDVQ PDV BOHMPSQSNHFP BSQ SFFLGV PDSP Y RF NRCVNH PE IV S FLIFPRP"
        "LPREQ AEO V.\nEPDVO BEGGEQ NVPPVOF RQ PDV VQUNRFD NSQULSUV RQBNLZV P, S"
        ", E, R, Q, F, SQZ D.PDV BOHMPSQSNHFP BSQ LFV PDRF RQAEOGSPREQ PE GSCV V"
        "ZLBSPVZ ULVFFVF SIELP PDV EPDVO FLIFPRPLPREQF RQ PDV BRMDVOPVYP.\nANSU{"
        " QEX_RJV_NVSOQVZ_GH_SIBF }";
      std::cout << "cipher: " << cipher2 << "\n\n";
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
      std::cout << "plaintext: " << mapCaesar(cipher2, key) << "\n\n";
    }


    // 0000 Challenge 3 - Transposition 
    {
      std::string cipher3 =
        "rs␣r␣enigm␣_aierhe␣i␣gluucsclhetersnti␣a␣rla␣t␣riayrgpetai␣diu␣Fawhiho}"
        "sipatfy␣ihr␣a␣rfa␣pes␣etohwrea␣octtonee␣eihetTpxcdeghi␣ro␣ped␣yGaledemX"
        "Toneepetlhtseghectnatanst␣ripctiharaics␣foarscee␣ebrn␣te␣doemrr␣c__ltcs"
        "aicsa␣coo␣wbrn␣_aranmeibti,haarhra,sipklti␣ci.ctst␣a␣lxtcnaenlkLeoakelX"
        "pohry␣patakrntd␣cilxsU␣inehe␣cwthers␣rpo␣narahhtr␣aienlsrtrr␣o.{rd___nX"
        "nti␣_ornrtoyrgoors␣te.ksip␣_crs␣_c␣pohelhgctn␣ie␣erntatecg␣teeeAsuvesuX";
      std::cout << "cipher: " << cipher3 << "\n\n";
      std::string plaintext = transpositionIteration(cipher3);
      std::cout << "plaintext: " << plaintext << "\n\n";
    }
  } // end 0000
  */

  /***
   * Problem Set 1837
   * Morse Code Translations
   */

  {
    {
      std::string code0 =
        "..-. .-. --- --/-.   .   .--/-.-- --- .-. -.-/.. .   ..   -   .. ../."
        ".- ... .-/-   . ./.-.. --- -. -.. --- -./..-   -.   ..   -   .   -../"
        "-.- .. -. --. -.. --- --/. ..   .   ..-.   ..-   .   ...   -/- ---/. "
        "  .-..   -   . ..   .-   .. .   -/..-. .-.. .- --./{-   . ..   ....- "
        "  -.   ---   ....-   -   â¸º   ....-   -.   -   ..   .. .}/--- -./. ."
        "   . ..   -..   .   . ../--- ..-./...   .   -.   -..   .   . ../--. -"
        "-- --- --. .-.. ./.. .   -   .-.";

      std::cout << "Code: " << code0 << "\n\n";
    }
  }
}