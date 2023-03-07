xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 265;
 9.11790;-0.26311;-12.76260;,
 7.84338;6.82115;-10.04627;,
 15.36058;0.07283;-3.88346;,
 13.13582;6.82153;-5.93420;,
 15.99127;4.83888;-3.62095;,
 15.99127;4.83888;-3.62095;,
 17.41381;5.59894;1.62178;,
 15.36058;0.07283;-3.88346;,
 15.70028;-0.16002;5.62152;,
 18.48696;4.07711;4.35398;,
 18.32504;2.17472;3.87155;,
 17.92715;1.70975;6.15690;,
 17.92715;1.70975;6.15690;,
 17.96320;3.63213;7.50018;,
 15.70028;-0.16002;5.62152;,
 13.15402;6.26472;11.04905;,
 10.46133;-1.10018;14.80946;,
 10.30653;6.32033;14.58752;,
 10.46133;-1.10018;14.80946;,
 10.30653;6.32033;14.58752;,
 -0.94950;-0.88093;18.30219;,
 7.24303;6.44318;15.45337;,
 2.97973;5.28635;17.06448;,
 -0.78907;2.23225;19.11015;,
 -12.46759;-1.02878;16.45277;,
 -0.94950;-0.88093;18.30219;,
 -0.78907;2.23225;19.11015;,
 -12.76458;0.17894;16.88947;,
 -12.76458;0.17894;16.88947;,
 -14.43278;2.42715;15.35406;,
 -12.46759;-1.02878;16.45277;,
 -19.93870;-0.82111;8.76431;,
 -17.61531;2.52471;11.75617;,
 -20.09050;1.33365;8.88319;,
 -19.93870;-0.82111;8.76431;,
 -20.09050;1.33365;8.88319;,
 -20.58557;-0.58755;-1.48203;,
 -20.16836;1.95963;7.57114;,
 -20.38972;2.70351;0.87239;,
 -20.68914;-0.13323;-1.48926;,
 -13.76242;-0.18880;-9.99928;,
 -20.58557;-0.58755;-1.48203;,
 -20.68914;-0.13323;-1.48926;,
 -13.69740;1.39207;-9.21947;,
 -5.93334;6.89698;-10.85180;,
 -4.63749;6.93283;-11.43305;,
 -13.69740;1.39207;-9.21947;,
 -1.85707;5.94437;-14.47284;,
 -2.56844;-0.32751;-17.93714;,
 -13.66888;-0.18333;-10.11605;,
 9.11790;-0.26311;-12.76260;,
 -2.56844;-0.32751;-17.93714;,
 7.84338;6.82115;-10.04627;,
 -1.85707;5.94437;-14.47284;,
 1.91144;6.87807;-11.41328;,
 10.30653;6.32033;14.58752;,
 13.15402;6.26472;11.04905;,
 9.91308;8.10275;9.39404;,
 8.60402;7.57285;12.56591;,
 7.84338;6.82115;-10.04627;,
 1.91144;6.87807;-11.41328;,
 1.29995;7.83198;-9.17559;,
 4.80276;7.70214;-8.42530;,
 4.69890;8.36537;-7.23408;,
 4.00032;10.49301;-7.02367;,
 8.59421;8.60801;-3.42969;,
 6.09771;10.55103;-5.49077;,
 7.26050;9.70588;-4.48713;,
 4.80276;7.70214;-8.42530;,
 1.29995;7.83198;-9.17559;,
 4.69890;8.36537;-7.23408;,
 4.00032;10.49301;-7.02367;,
 -4.48956;9.16956;-8.25071;,
 1.47209;11.43037;-7.72728;,
 -3.68392;10.44951;-7.89932;,
 9.02063;9.09676;-0.42800;,
 15.05570;7.19957;-0.37445;,
 13.53251;7.45635;-3.48259;,
 8.59421;8.60801;-3.42969;,
 8.64167;10.08155;1.86399;,
 5.61254;10.92619;-3.72618;,
 7.49025;9.73566;6.65944;,
 3.91458;12.58095;-4.86836;,
 -0.97041;14.86646;-2.15644;,
 5.69833;9.61624;7.47156;,
 1.10780;10.44648;8.25914;,
 -1.26768;14.71123;-1.27820;,
 -1.46296;12.25442;4.65875;,
 7.26050;9.70588;-4.48713;,
 8.87552;9.73548;0.58066;,
 9.02063;9.09676;-0.42800;,
 8.59421;8.60801;-3.42969;,
 4.00032;10.49301;-7.02367;,
 1.47209;11.43037;-7.72728;,
 6.09771;10.55103;-5.49077;,
 5.29783;11.64355;-5.22533;,
 0.92388;13.99881;-6.25867;,
 4.38878;12.36015;-5.30601;,
 7.26050;9.70588;-4.48713;,
 6.09771;10.55103;-5.49077;,
 8.87552;9.73548;0.58066;,
 5.29783;11.64355;-5.22533;,
 8.64167;10.08155;1.86399;,
 5.61254;10.92619;-3.72618;,
 9.91308;8.10275;9.39404;,
 7.49025;9.73566;6.65944;,
 8.60402;7.57285;12.56591;,
 3.72269;9.01040;10.80528;,
 5.69833;9.61624;7.47156;,
 3.68943;9.02779;10.76492;,
 5.69833;9.61624;7.47156;,
 1.10780;10.44648;8.25914;,
 2.87360;9.25580;10.21835;,
 3.68943;9.02779;10.76492;,
 -5.96847;7.62664;-9.46283;,
 -5.93334;6.89698;-10.85180;,
 -18.56821;4.34233;0.83009;,
 -20.38972;2.70351;0.87239;,
 -13.69740;1.39207;-9.21947;,
 -20.68914;-0.13323;-1.48926;,
 -15.17274;5.65659;9.49531;,
 -15.34688;5.59545;9.25199;,
 -17.14467;4.17333;9.68368;,
 -13.21772;6.77749;5.50142;,
 -18.56821;4.34233;0.83009;,
 -20.16836;1.95963;7.57114;,
 -20.38972;2.70351;0.87239;,
 10.30653;6.32033;14.58752;,
 8.60402;7.57285;12.56591;,
 7.24303;6.44318;15.45337;,
 3.72269;9.01040;10.80528;,
 4.29424;6.94515;15.17517;,
 3.70703;7.88181;12.69587;,
 3.26088;8.91753;11.04159;,
 3.72269;9.01040;10.80528;,
 3.68943;9.02779;10.76492;,
 3.26088;8.91753;11.04159;,
 2.87360;9.25580;10.21835;,
 2.82725;9.01755;10.82625;,
 4.38878;12.36015;-5.30601;,
 3.91458;12.58095;-4.86836;,
 5.61254;10.92619;-3.72618;,
 5.29783;11.64355;-5.22533;,
 -1.58073;15.16867;-4.54765;,
 -2.79820;14.76337;-2.50741;,
 -1.26768;14.71123;-1.27820;,
 -0.97041;14.86646;-2.15644;,
 -15.00611;5.64741;9.66258;,
 -15.34688;5.59545;9.25199;,
 -15.17274;5.65659;9.49531;,
 -7.71549;8.00091;7.64647;,
 -8.25414;9.09938;5.36094;,
 -11.03221;6.90675;9.82646;,
 -13.21772;6.77749;5.50142;,
 -15.00611;5.64741;9.66258;,
 -15.34688;5.59545;9.25199;,
 4.29424;6.94515;15.17517;,
 3.70703;7.88181;12.69587;,
 2.97973;5.28635;17.06448;,
 -1.16043;8.74851;10.64341;,
 -0.78907;2.23225;19.11015;,
 -12.76458;0.17894;16.88947;,
 -3.89055;8.94887;9.93660;,
 -5.96789;7.88418;9.75517;,
 -10.60827;6.47478;12.35798;,
 -14.43278;2.42715;15.35406;,
 3.26088;8.91753;11.04159;,
 2.82725;9.01755;10.82625;,
 -1.16043;8.74851;10.64341;,
 3.70703;7.88181;12.69587;,
 -5.96789;7.88418;9.75517;,
 -7.71549;8.00091;7.64647;,
 -11.03221;6.90675;9.82646;,
 -10.60827;6.47478;12.35798;,
 -10.60827;6.47478;12.35798;,
 -11.03221;6.90675;9.82646;,
 -14.43278;2.42715;15.35406;,
 -15.00611;5.64741;9.66258;,
 -17.61531;2.52471;11.75617;,
 -15.17274;5.65659;9.49531;,
 -17.14467;4.17333;9.68368;,
 4.38878;12.36015;-5.30601;,
 0.92388;13.99881;-6.25867;,
 3.91458;12.58095;-4.86836;,
 -0.97041;14.86646;-2.15644;,
 -1.31119;15.04626;-5.30231;,
 -1.58073;15.16867;-4.54765;,
 0.92388;13.99881;-6.25867;,
 1.47209;11.43037;-7.72728;,
 -3.68392;10.44951;-7.89932;,
 -1.31119;15.04626;-5.30231;,
 -1.46296;12.25442;4.65875;,
 -1.26768;14.71123;-1.27820;,
 -6.58703;9.89177;6.55715;,
 -2.79820;14.76337;-2.50741;,
 -8.06136;9.92952;4.88103;,
 2.82725;9.01755;10.82625;,
 2.87360;9.25580;10.21835;,
 -1.16043;8.74851;10.64341;,
 1.10780;10.44648;8.25914;,
 -1.46296;12.25442;4.65875;,
 -3.89055;8.94887;9.93660;,
 -6.58703;9.89177;6.55715;,
 -3.89055;8.94887;9.93660;,
 -6.58703;9.89177;6.55715;,
 -5.96789;7.88418;9.75517;,
 -7.71549;8.00091;7.64647;,
 -8.06136;9.92952;4.88103;,
 -8.25414;9.09938;5.36094;,
 -5.50884;7.93662;-9.18825;,
 -4.63749;6.93283;-11.43305;,
 -5.93334;6.89698;-10.85180;,
 -5.96847;7.62664;-9.46283;,
 1.91144;6.87807;-11.41328;,
 -1.85707;5.94437;-14.47284;,
 1.29995;7.83198;-9.17559;,
 -4.48956;9.16956;-8.25071;,
 -4.63749;6.93283;-11.43305;,
 -5.50884;7.93662;-9.18825;,
 -2.79820;14.76337;-2.50741;,
 -1.58073;15.16867;-4.54765;,
 -8.06136;9.92952;4.88103;,
 -1.31119;15.04626;-5.30231;,
 -3.68392;10.44951;-7.89932;,
 -8.25414;9.09938;5.36094;,
 -13.21772;6.77749;5.50142;,
 -18.56821;4.34233;0.83009;,
 -4.48956;9.16956;-8.25071;,
 -5.50884;7.93662;-9.18825;,
 -5.96847;7.62664;-9.46283;,
 17.41381;5.59894;1.62178;,
 15.05570;7.19957;-0.37445;,
 18.48696;4.07711;4.35398;,
 17.96320;3.63213;7.50018;,
 9.02063;9.09676;-0.42800;,
 13.15402;6.26472;11.04905;,
 8.87552;9.73548;0.58066;,
 8.64167;10.08155;1.86399;,
 7.49025;9.73566;6.65944;,
 9.91308;8.10275;9.39404;,
 15.99127;4.83888;-3.62095;,
 13.13582;6.82153;-5.93420;,
 17.41381;5.59894;1.62178;,
 13.53251;7.45635;-3.48259;,
 15.05570;7.19957;-0.37445;,
 13.13582;6.82153;-5.93420;,
 7.84338;6.82115;-10.04627;,
 13.53251;7.45635;-3.48259;,
 8.59421;8.60801;-3.42969;,
 4.80276;7.70214;-8.42530;,
 4.69890;8.36537;-7.23408;,
 18.32504;2.17472;3.87155;,
 18.48696;4.07711;4.35398;,
 17.96320;3.63213;7.50018;,
 17.92715;1.70975;6.15690;,
 7.24303;6.44318;15.45337;,
 4.29424;6.94515;15.17517;,
 2.97973;5.28635;17.06448;,
 -17.61531;2.52471;11.75617;,
 -17.14467;4.17333;9.68368;,
 -20.16836;1.95963;7.57114;,
 -20.09050;1.33365;8.88319;,
 -1.90109;-1.91724;2.11563;,
 -13.76242;-0.18880;-9.99928;,
 -13.66888;-0.18333;-10.11605;;
 
 163;
 3;0,1,2;,
 3;1,3,2;,
 3;3,4,2;,
 3;5,6,7;,
 3;7,6,8;,
 3;6,9,10;,
 3;6,10,8;,
 3;10,11,8;,
 3;12,13,14;,
 3;13,15,14;,
 3;14,15,16;,
 3;15,17,16;,
 3;18,19,20;,
 3;19,21,20;,
 3;21,22,20;,
 3;22,23,20;,
 4;24,25,26,27;,
 3;28,29,30;,
 3;30,29,31;,
 3;29,32,31;,
 3;32,33,31;,
 3;34,35,36;,
 3;35,37,36;,
 3;37,38,36;,
 3;38,39,36;,
 4;40,41,42,43;,
 3;44,45,46;,
 3;45,47,46;,
 3;47,48,46;,
 3;48,49,46;,
 3;50,51,52;,
 3;51,53,52;,
 3;53,54,52;,
 4;55,56,57,58;,
 4;59,60,61,62;,
 3;63,64,65;,
 3;64,66,65;,
 3;66,67,65;,
 3;68,69,70;,
 3;70,69,71;,
 3;69,72,71;,
 3;71,72,73;,
 3;72,74,73;,
 4;75,76,77,78;,
 3;79,80,81;,
 3;80,82,81;,
 3;82,83,81;,
 3;81,83,84;,
 3;84,83,85;,
 3;83,86,85;,
 3;86,87,85;,
 4;88,89,90,91;,
 3;92,93,94;,
 3;94,93,95;,
 3;93,96,95;,
 3;96,97,95;,
 3;98,99,100;,
 3;99,101,100;,
 3;100,101,102;,
 3;101,103,102;,
 3;104,105,106;,
 3;106,105,107;,
 3;105,108,107;,
 3;108,109,107;,
 4;110,111,112,113;,
 3;114,115,116;,
 3;116,115,117;,
 3;115,118,117;,
 3;118,119,117;,
 3;120,121,122;,
 3;121,123,122;,
 3;123,124,122;,
 3;122,124,125;,
 3;124,126,125;,
 3;127,128,129;,
 3;128,130,129;,
 3;129,130,131;,
 3;131,130,132;,
 3;130,133,132;,
 3;134,135,136;,
 3;135,137,136;,
 3;137,138,136;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 3;147,148,149;,
 3;150,151,152;,
 3;151,153,152;,
 3;152,153,154;,
 3;153,155,154;,
 3;156,157,158;,
 3;157,159,158;,
 3;158,159,160;,
 3;160,159,161;,
 3;159,162,161;,
 3;162,163,161;,
 3;163,164,161;,
 3;164,165,161;,
 4;166,167,168,169;,
 4;170,171,172,173;,
 3;174,175,176;,
 3;175,177,176;,
 3;176,177,178;,
 3;177,179,178;,
 3;179,180,178;,
 3;181,182,183;,
 3;183,182,184;,
 3;182,185,184;,
 3;185,186,184;,
 4;187,188,189,190;,
 3;191,192,193;,
 3;192,194,193;,
 3;194,195,193;,
 3;196,197,198;,
 3;197,199,198;,
 3;199,200,198;,
 3;198,200,201;,
 3;200,202,201;,
 3;203,204,205;,
 3;205,204,206;,
 3;204,207,206;,
 3;207,208,206;,
 4;209,210,211,212;,
 3;213,214,215;,
 3;215,214,216;,
 3;214,217,216;,
 3;217,218,216;,
 3;219,220,221;,
 3;220,222,221;,
 3;222,223,221;,
 3;221,223,224;,
 3;224,223,225;,
 3;225,223,226;,
 3;223,227,226;,
 3;227,228,226;,
 3;228,229,226;,
 3;230,231,232;,
 3;232,231,233;,
 3;231,234,233;,
 3;233,234,235;,
 3;234,236,235;,
 3;236,237,235;,
 3;237,238,235;,
 3;238,239,235;,
 3;240,241,242;,
 3;241,243,242;,
 3;243,244,242;,
 3;245,246,247;,
 3;247,246,248;,
 3;246,249,248;,
 3;249,250,248;,
 4;251,252,253,254;,
 3;255,256,257;,
 4;258,259,260,261;,
 4;262,24,31,36;,
 3;262,16,20;,
 4;262,263,264,48;,
 3;264,40,43;,
 3;8,16,262;,
 3;7,8,262;,
 3;263,262,36;,
 3;24,262,20;,
 3;50,7,262;,
 3;50,262,48;;
 
 MeshMaterialList {
  11;
  163;
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7;;
  Material {
   0.440000;0.480000;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  126;
  0.849915;-0.033465;-0.525856;,
  0.583837;0.380108;-0.717392;,
  0.359920;0.730390;-0.580507;,
  0.654083;0.507151;-0.561225;,
  0.848511;0.191915;-0.493151;,
  0.897867;-0.414797;0.147574;,
  0.914451;0.293681;-0.278444;,
  0.992261;-0.056406;-0.110616;,
  0.942860;-0.319685;-0.093894;,
  0.748622;-0.563423;0.349457;,
  0.684035;0.000468;0.729449;,
  0.276308;-0.553956;0.785358;,
  0.695393;-0.212183;0.686591;,
  0.467508;0.047429;0.882716;,
  0.292672;-0.099213;0.951052;,
  0.251951;0.271254;0.928946;,
  0.389966;0.172891;0.904453;,
  0.254367;-0.287184;0.923484;,
  -0.608426;-0.303786;0.733166;,
  -0.546111;-0.366625;0.753226;,
  -0.833084;-0.109316;0.542237;,
  -0.785136;0.034015;0.618389;,
  -0.666675;0.484383;0.566496;,
  -0.942939;0.123425;0.309244;,
  -0.998729;-0.039631;-0.031129;,
  -0.872261;0.468008;0.141877;,
  -0.949433;0.313904;-0.006442;,
  -0.911475;-0.202082;0.358296;,
  -0.640717;0.370965;-0.672211;,
  -0.604118;0.427778;-0.672345;,
  -0.085448;0.470049;-0.878495;,
  -0.486644;0.667965;-0.563028;,
  -0.393966;0.672786;-0.626218;,
  -0.102412;0.779938;-0.617421;,
  0.092043;0.921737;-0.376735;,
  0.360791;0.901856;0.237665;,
  0.219224;0.913640;0.342349;,
  0.164461;0.798167;-0.579553;,
  0.184660;0.904025;-0.385537;,
  0.562246;0.637218;-0.527098;,
  0.438720;0.602185;-0.667007;,
  0.425607;0.272381;-0.862941;,
  0.654937;0.499760;-0.566831;,
  0.743663;0.577247;-0.337270;,
  -0.220833;0.628646;-0.745679;,
  -0.241052;0.462688;-0.853120;,
  0.251990;0.407766;-0.877626;,
  0.566467;0.822915;-0.043879;,
  0.423200;0.900321;0.101605;,
  0.431094;0.864079;-0.259855;,
  0.475598;0.879311;0.024880;,
  0.491963;0.864525;0.102806;,
  0.530077;0.845971;0.057896;,
  0.309201;0.936635;0.164649;,
  -0.024473;0.946662;0.321297;,
  -0.118361;0.888620;0.443108;,
  0.126763;0.906569;0.402571;,
  0.141444;0.942400;0.303110;,
  0.313702;0.930839;0.187429;,
  0.732250;0.656894;-0.179719;,
  0.599483;0.672531;-0.433961;,
  0.395809;0.801347;-0.448529;,
  0.479903;0.763519;-0.432125;,
  0.088529;0.938275;0.334370;,
  0.009929;0.926499;0.376167;,
  0.015994;0.919481;0.392810;,
  -0.562826;0.796420;-0.221231;,
  -0.408549;0.829683;-0.380411;,
  -0.601972;0.775678;0.189615;,
  -0.519670;0.756138;0.397741;,
  -0.514533;0.854105;0.075893;,
  -0.426293;0.903336;0.047518;,
  0.012212;0.898076;0.439671;,
  -0.226763;0.840327;0.492371;,
  -0.230873;0.830742;0.506524;,
  -0.042350;0.903781;0.425895;,
  0.177808;0.980922;0.078590;,
  -0.235323;0.929637;0.283547;,
  0.604768;0.554090;-0.572048;,
  -0.310523;0.906347;0.286548;,
  -0.465057;0.766330;0.443237;,
  -0.455373;0.851070;0.261372;,
  -0.123694;0.828691;0.545867;,
  -0.265463;0.803020;0.533562;,
  -0.285890;0.787075;0.546608;,
  -0.131306;0.795246;0.591897;,
  0.426280;0.904575;0.005523;,
  -0.828475;0.557093;0.057241;,
  -0.392514;0.805200;0.444506;,
  -0.415883;0.809669;-0.414099;,
  -0.756734;0.198368;-0.622900;,
  0.020655;-0.999469;-0.025188;,
  -0.055078;-0.558467;-0.827696;,
  0.058071;-0.941663;-0.331509;,
  -0.740033;0.298598;-0.602653;,
  0.254604;0.900040;0.353701;,
  0.566022;0.821643;0.067238;,
  0.261135;0.956766;-0.128096;,
  -0.631079;0.639798;0.438631;,
  -0.581054;0.655880;-0.481869;,
  0.129619;0.900597;0.414878;,
  0.586465;0.771671;0.246136;,
  -0.379942;0.855446;0.351932;,
  -0.263793;0.819725;0.508394;,
  -0.265345;0.758403;0.595329;,
  -0.100097;0.696699;0.710346;,
  -0.311804;0.772668;0.552958;,
  -0.641645;0.538208;-0.546466;,
  -0.856591;0.217389;-0.467968;,
  -0.855484;0.304722;-0.418679;,
  -0.716015;0.673597;-0.183275;,
  -0.945939;0.033146;-0.322648;,
  0.273837;0.881932;0.383677;,
  0.387143;0.873298;0.295754;,
  0.429866;0.884131;0.183102;,
  0.981838;-0.120693;0.146384;,
  -0.028602;-0.999040;0.033170;,
  -0.059726;-0.998212;0.002536;,
  -0.056699;-0.997443;-0.043509;,
  0.053960;-0.998474;0.011717;,
  0.001475;-0.997961;0.063806;,
  -0.056892;-0.994647;-0.086262;,
  -0.060231;-0.994723;-0.083061;,
  -0.009601;-0.996603;-0.081796;,
  0.103726;-0.994113;-0.031315;,
  0.071885;-0.995756;-0.057468;;
  163;
  3;1,2,0;,
  3;2,3,0;,
  3;3,4,0;,
  3;4,6,0;,
  3;0,6,5;,
  3;6,7,8;,
  3;92,92,93;,
  3;8,9,5;,
  3;9,11,11;,
  3;11,12,11;,
  3;5,12,10;,
  3;12,13,10;,
  3;10,13,14;,
  3;13,15,14;,
  3;15,16,14;,
  3;16,17,14;,
  4;18,14,17,19;,
  3;19,21,18;,
  3;18,21,20;,
  3;21,22,20;,
  3;22,23,20;,
  3;20,23,24;,
  3;23,25,24;,
  3;25,26,24;,
  3;26,27,24;,
  4;90,24,94,29;,
  3;31,32,29;,
  3;32,33,29;,
  3;33,30,29;,
  3;30,28,29;,
  3;1,30,2;,
  3;30,33,2;,
  3;33,34,2;,
  4;95,96,35,36;,
  4;2,34,37,38;,
  3;40,41,39;,
  3;41,42,39;,
  3;42,43,39;,
  3;38,37,40;,
  3;40,37,41;,
  3;37,44,41;,
  3;41,44,46;,
  3;44,45,46;,
  4;47,48,49,97;,
  3;50,51,58;,
  3;51,52,58;,
  3;52,53,58;,
  3;58,53,57;,
  3;57,53,56;,
  3;53,54,56;,
  3;54,55,56;,
  4;43,59,47,39;,
  3;41,46,42;,
  3;42,46,60;,
  3;46,61,60;,
  3;61,62,60;,
  3;43,42,59;,
  3;42,60,59;,
  3;59,60,50;,
  3;98,98,98;,
  3;35,58,36;,
  3;36,58,64;,
  3;58,57,64;,
  3;57,63,64;,
  4;57,56,65,63;,
  3;67,31,66;,
  3;66,31,99;,
  3;31,29,99;,
  3;29,94,26;,
  3;69,70,68;,
  3;70,71,68;,
  3;71,66,68;,
  3;68,66,25;,
  3;66,26,25;,
  3;95,36,100;,
  3;36,64,100;,
  3;100,64,74;,
  3;74,64,73;,
  3;64,72,73;,
  3;64,63,72;,
  3;63,65,72;,
  3;65,75,72;,
  4;101,52,51,60;,
  4;76,77,54,53;,
  3;78,78,78;,
  3;80,81,79;,
  3;81,71,79;,
  3;79,71,102;,
  3;71,70,102;,
  3;74,73,103;,
  3;73,82,103;,
  3;103,82,104;,
  3;104,82,105;,
  3;82,83,105;,
  3;83,84,105;,
  3;84,85,105;,
  3;85,106,105;,
  4;72,75,82,73;,
  4;84,80,79,85;,
  3;85,79,106;,
  3;79,102,106;,
  3;21,102,22;,
  3;102,69,22;,
  3;69,68,22;,
  3;62,61,52;,
  3;52,61,53;,
  3;61,86,53;,
  3;86,76,53;,
  4;61,46,45,107;,
  3;55,54,88;,
  3;54,77,88;,
  3;77,87,88;,
  3;75,65,82;,
  3;65,56,82;,
  3;56,55,82;,
  3;82,55,83;,
  3;55,88,83;,
  3;83,88,84;,
  3;84,88,80;,
  3;88,87,80;,
  3;87,81,80;,
  4;89,32,31,67;,
  3;34,33,37;,
  3;37,33,44;,
  3;33,32,44;,
  3;32,89,44;,
  3;108,109,108;,
  3;109,107,87;,
  3;107,110,87;,
  3;87,110,111;,
  3;81,110,71;,
  3;71,110,66;,
  3;45,44,66;,
  3;44,89,66;,
  3;89,67,66;,
  3;112,48,113;,
  3;113,48,114;,
  3;48,47,114;,
  3;114,47,96;,
  3;47,59,96;,
  3;59,50,96;,
  3;50,58,96;,
  3;58,35,96;,
  3;4,3,6;,
  3;3,49,6;,
  3;49,48,6;,
  3;3,2,49;,
  3;49,2,39;,
  3;2,38,39;,
  3;38,40,39;,
  4;8,7,115,9;,
  3;15,74,16;,
  4;22,68,25,23;,
  4;91,116,117,118;,
  3;91,119,120;,
  4;91,121,122,123;,
  3;28,90,29;,
  3;93,119,91;,
  3;124,93,91;,
  3;121,91,118;,
  3;116,91,120;,
  3;125,124,91;,
  3;125,91,123;;
 }
 MeshTextureCoords {
  265;
  0.796571;0.556807;,
  0.797726;0.696718;,
  0.878242;0.572542;,
  0.848393;0.700690;,
  0.878242;0.664691;,
  0.913830;0.278854;,
  0.872773;0.260343;,
  0.913830;0.370983;,
  0.842343;0.370821;,
  0.849548;0.287059;,
  0.852199;0.323899;,
  0.835601;0.332239;,
  0.203214;0.185392;,
  0.210994;0.223615;,
  0.211079;0.147876;,
  0.255855;0.275205;,
  0.290684;0.134749;,
  0.290684;0.277857;,
  0.825097;0.370983;,
  0.825097;0.227362;,
  0.733694;0.364773;,
  0.800747;0.224489;,
  0.765721;0.246018;,
  0.733015;0.304106;,
  0.531488;0.806035;,
  0.531488;0.716312;,
  0.470812;0.711589;,
  0.507631;0.806787;,
  0.162601;0.116605;,
  0.119981;0.134296;,
  0.186347;0.117363;,
  0.186347;0.199726;,
  0.120070;0.171213;,
  0.144639;0.200160;,
  0.605237;0.711589;,
  0.563521;0.711589;,
  0.607025;0.790493;,
  0.552234;0.721925;,
  0.541992;0.773654;,
  0.598246;0.790772;,
  0.191619;0.103499;,
  0.191619;0.019529;,
  0.182807;0.019473;,
  0.165186;0.106078;,
  0.564185;0.314447;,
  0.574903;0.315912;,
  0.518495;0.197067;,
  0.606787;0.296334;,
  0.625075;0.171647;,
  0.520848;0.171647;,
  0.831028;0.384792;,
  0.733015;0.381510;,
  0.831028;0.525091;,
  0.749168;0.506488;,
  0.785015;0.527412;,
  0.475963;0.011162;,
  0.441027;0.011162;,
  0.449375;0.055041;,
  0.473884;0.042019;,
  0.662001;0.052964;,
  0.662001;0.006184;,
  0.635652;0.005263;,
  0.637308;0.032821;,
  0.952915;0.391048;,
  0.911511;0.394594;,
  0.952915;0.433359;,
  0.912930;0.414501;,
  0.930411;0.423689;,
  0.565933;0.161120;,
  0.579456;0.137144;,
  0.553328;0.153505;,
  0.521827;0.126664;,
  0.579456;0.085757;,
  0.518495;0.100500;,
  0.555127;0.077524;,
  0.993247;0.458401;,
  0.993247;0.399344;,
  0.969224;0.410705;,
  0.968111;0.454590;,
  0.831693;0.128547;,
  0.836893;0.174840;,
  0.852561;0.096871;,
  0.857882;0.201115;,
  0.917180;0.213963;,
  0.864838;0.092583;,
  0.902067;0.101487;,
  0.920659;0.207284;,
  0.920659;0.145319;,
  0.989219;0.134152;,
  0.989219;0.093164;,
  0.976486;0.101100;,
  0.966573;0.124804;,
  0.897041;0.009675;,
  0.881523;0.031624;,
  0.916950;0.008070;,
  0.916950;0.030313;,
  0.893484;0.082057;,
  0.913451;0.045426;,
  0.788052;0.048070;,
  0.799157;0.064365;,
  0.807251;0.012094;,
  0.818794;0.073602;,
  0.818794;0.007627;,
  0.813907;0.057992;,
  0.403598;0.718468;,
  0.386878;0.756035;,
  0.430928;0.714585;,
  0.430928;0.762746;,
  0.399534;0.763833;,
  0.430712;0.763210;,
  0.888746;0.538540;,
  0.905760;0.573999;,
  0.918368;0.546818;,
  0.919878;0.538540;,
  0.109477;0.235409;,
  0.091315;0.235354;,
  0.109477;0.373484;,
  0.084087;0.397034;,
  0.005252;0.327308;,
  0.027705;0.412428;,
  0.884421;0.728158;,
  0.883150;0.730446;,
  0.895806;0.758512;,
  0.848183;0.713943;,
  0.832487;0.785385;,
  0.895806;0.810643;,
  0.843708;0.818016;,
  0.078817;0.098523;,
  0.092640;0.070914;,
  0.062200;0.080560;,
  0.092640;0.022751;,
  0.055016;0.056942;,
  0.072799;0.038441;,
  0.088544;0.021435;,
  0.812198;0.722178;,
  0.812469;0.721271;,
  0.804384;0.720555;,
  0.812469;0.705350;,
  0.803471;0.712946;,
  0.809719;0.761771;,
  0.814632;0.766290;,
  0.814632;0.731061;,
  0.806273;0.746643;,
  0.850514;0.249816;,
  0.850514;0.230290;,
  0.835601;0.228179;,
  0.837095;0.235617;,
  0.504553;0.450359;,
  0.504553;0.437658;,
  0.497045;0.445745;,
  0.132588;0.094521;,
  0.154682;0.106078;,
  0.119981;0.060871;,
  0.154682;0.047863;,
  0.124565;0.021990;,
  0.127986;0.019482;,
  0.486881;0.316662;,
  0.470119;0.298859;,
  0.493925;0.351815;,
  0.426682;0.297647;,
  0.493925;0.418611;,
  0.421302;0.489502;,
  0.405366;0.302458;,
  0.397788;0.326771;,
  0.383278;0.370499;,
  0.391825;0.455517;,
  0.441859;0.734816;,
  0.441431;0.738944;,
  0.460091;0.763833;,
  0.460091;0.720254;,
  0.575850;0.018488;,
  0.554953;0.020980;,
  0.557161;0.057492;,
  0.575850;0.066998;,
  0.430523;0.059598;,
  0.413693;0.048864;,
  0.430523;0.145168;,
  0.393181;0.081202;,
  0.393696;0.145899;,
  0.391370;0.081207;,
  0.383278;0.112532;,
  0.989166;0.144678;,
  0.968606;0.180979;,
  0.990412;0.151243;,
  0.990412;0.213817;,
  0.966573;0.208810;,
  0.970897;0.213963;,
  0.959613;0.624584;,
  0.945561;0.674471;,
  0.980807;0.700690;,
  0.980807;0.606502;,
  0.907974;0.804933;,
  0.933307;0.863686;,
  0.931445;0.748155;,
  0.948318;0.864558;,
  0.948318;0.750549;,
  0.689592;0.146460;,
  0.692311;0.140819;,
  0.660293;0.136506;,
  0.691903;0.111075;,
  0.692311;0.063491;,
  0.643936;0.122119;,
  0.635652;0.086353;,
  0.958207;0.278462;,
  0.958207;0.241397;,
  0.932265;0.278147;,
  0.924333;0.258628;,
  0.950664;0.226004;,
  0.937017;0.234745;,
  0.719162;0.087784;,
  0.719162;0.060182;,
  0.709419;0.065073;,
  0.713755;0.082775;,
  0.244753;0.053171;,
  0.203214;0.053171;,
  0.260025;0.074637;,
  0.246882;0.124223;,
  0.210193;0.089702;,
  0.224639;0.113164;,
  0.435769;0.989536;,
  0.454549;0.994737;,
  0.357282;0.910781;,
  0.460308;0.991487;,
  0.460308;0.899442;,
  0.351430;0.897295;,
  0.329913;0.843566;,
  0.340265;0.774359;,
  0.457293;0.874349;,
  0.457795;0.847922;,
  0.457572;0.840584;,
  0.640801;0.200177;,
  0.635652;0.238151;,
  0.654557;0.167339;,
  0.677679;0.156986;,
  0.654110;0.292214;,
  0.721217;0.211145;,
  0.663319;0.300950;,
  0.674048;0.305010;,
  0.710917;0.295829;,
  0.721217;0.255786;,
  0.777548;0.066834;,
  0.777548;0.020019;,
  0.733015;0.073602;,
  0.754355;0.017901;,
  0.733950;0.035289;,
  0.301187;0.053998;,
  0.309462;0.104848;,
  0.316910;0.036787;,
  0.354290;0.059918;,
  0.340629;0.110155;,
  0.354290;0.102246;,
  0.678747;0.016219;,
  0.672505;0.052964;,
  0.697989;0.052386;,
  0.697989;0.013150;,
  0.507819;0.013857;,
  0.486466;0.026196;,
  0.507820;0.055041;,
  0.968111;0.504746;,
  0.994748;0.527412;,
  0.994748;0.475198;,
  0.980797;0.468927;,
  0.678119;0.599829;,
  0.197237;0.113926;,
  0.191619;0.104651;;
 }
}
