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
 238;
 0.43272;0.01393;2.97864;,
 5.58743;-0.18511;0.57169;,
 5.58320;3.08746;1.80922;,
 -0.89253;3.08746;5.66808;,
 0.43272;0.01393;2.97864;,
 -0.89253;3.08746;5.66808;,
 -3.64163;0.02599;3.16281;,
 -2.77774;3.08746;5.90727;,
 -5.36954;1.13240;4.97242;,
 -3.64163;0.02599;3.16281;,
 -5.36954;1.13240;4.97242;,
 -6.06897;-0.20496;1.23758;,
 -7.83015;3.08746;4.24620;,
 -8.70858;3.08746;2.77577;,
 -6.06897;-0.20496;1.23758;,
 -8.70858;3.08746;2.77577;,
 -4.41395;-0.09712;-3.05309;,
 -7.52663;3.08746;-0.18285;,
 -5.08164;1.01497;-2.96471;,
 -0.49772;-0.16499;-7.41557;,
 -4.41395;-0.09712;-3.05309;,
 -5.08164;1.01497;-2.96471;,
 -0.60603;0.25143;-7.55135;,
 -0.49772;-0.16499;-7.41557;,
 -0.60603;0.25143;-7.55135;,
 4.76240;-0.16819;-10.28340;,
 0.42783;1.05755;-8.41310;,
 4.22879;1.05339;-10.36053;,
 4.84587;0.75118;-10.55094;,
 9.23095;-0.18711;-10.58798;,
 4.76240;-0.16819;-10.28340;,
 9.27340;-0.03296;-10.63342;,
 8.52818;1.00971;-10.87072;,
 4.84587;0.75118;-10.55094;,
 10.96214;-0.13269;-8.02554;,
 9.23095;-0.18711;-10.58798;,
 9.27340;-0.03296;-10.63342;,
 11.19032;0.33362;-8.14316;,
 11.19032;0.33362;-8.14316;,
 11.34531;3.08746;-5.41238;,
 10.96214;-0.13269;-8.02554;,
 9.91108;-0.25653;-3.85943;,
 10.80161;3.08746;-3.51747;,
 5.58743;-0.18511;0.57169;,
 9.91108;-0.25653;-3.85943;,
 10.80161;3.08746;-3.51747;,
 5.58320;3.08746;1.80922;,
 5.58320;3.08746;1.80922;,
 5.24610;4.36339;2.02572;,
 -0.89253;3.08746;5.66808;,
 2.87506;6.38617;3.34584;,
 -1.51955;6.37170;5.72217;,
 -8.70858;3.08746;2.77577;,
 -7.83015;3.08746;4.24620;,
 -8.06635;4.77796;4.33204;,
 -8.89055;4.22696;2.93422;,
 11.34531;3.08746;-5.41238;,
 10.95839;3.78330;-5.13923;,
 10.80161;3.08746;-3.51747;,
 10.35632;4.48150;-4.12211;,
 10.25861;4.18439;-3.29751;,
 10.80161;3.08746;-3.51747;,
 10.25861;4.18439;-3.29751;,
 5.58320;3.08746;1.80922;,
 10.03370;4.35123;-3.11281;,
 5.24610;4.36339;2.02572;,
 2.87506;6.38617;3.34584;,
 0.20870;9.76600;4.26235;,
 -1.51955;6.37170;5.72217;,
 -1.33046;9.83778;5.16424;,
 -1.69361;9.30000;5.45838;,
 10.03370;4.35123;-3.11281;,
 7.88568;6.27686;-1.99450;,
 5.24610;4.36339;2.02572;,
 3.58821;9.23870;0.89936;,
 2.87506;6.38617;3.34584;,
 0.82471;10.24666;3.33578;,
 0.20870;9.76600;4.26235;,
 -3.68102;6.43148;5.97231;,
 -2.77774;3.08746;5.90727;,
 -0.89253;3.08746;5.66808;,
 -1.51955;6.37170;5.72217;,
 -2.77774;3.08746;5.90727;,
 -3.68102;6.43148;5.97231;,
 -5.36954;1.13240;4.97242;,
 -4.19539;7.78399;5.82332;,
 -4.76766;7.87672;5.60682;,
 -7.31352;6.49331;4.68946;,
 -7.83015;3.08746;4.24620;,
 -8.06635;4.77796;4.33204;,
 -1.44386;10.55209;4.34153;,
 -1.70227;11.31206;2.41724;,
 -2.03989;9.92087;4.96688;,
 -4.76766;7.87672;5.60682;,
 -4.24148;10.50756;1.07852;,
 -7.31352;6.49331;4.68946;,
 -4.63668;10.27763;1.09260;,
 -7.61217;6.77137;3.95116;,
 -1.69361;9.30000;5.45838;,
 -4.19539;7.78399;5.82332;,
 -3.68102;6.43148;5.97231;,
 -1.51955;6.37170;5.72217;,
 0.82471;10.24666;3.33578;,
 -0.28751;11.11543;3.18664;,
 0.20870;9.76600;4.26235;,
 -1.33046;9.83778;5.16424;,
 -1.34363;10.48392;4.52965;,
 -1.47564;10.22183;4.87391;,
 -1.33046;9.83778;5.16424;,
 -1.47564;10.22183;4.87391;,
 -1.69361;9.30000;5.45838;,
 -2.03989;9.92087;4.96688;,
 -4.19539;7.78399;5.82332;,
 -4.76766;7.87672;5.60682;,
 -7.31352;6.49331;4.68946;,
 -7.61217;6.77137;3.95116;,
 -8.06635;4.77796;4.33204;,
 -8.68814;6.06439;2.04780;,
 -8.89055;4.22696;2.93422;,
 -8.69743;6.04341;2.04081;,
 -4.63668;10.27763;1.09260;,
 -4.94534;10.03941;1.00339;,
 -7.61217;6.77137;3.95116;,
 -6.18922;8.94804;0.92285;,
 -8.68814;6.06439;2.04780;,
 9.27340;-0.03296;-10.63342;,
 8.52818;1.00971;-10.87072;,
 11.19032;0.33362;-8.14316;,
 8.38052;1.70239;-10.55815;,
 10.95839;3.78330;-5.13923;,
 11.34531;3.08746;-5.41238;,
 8.38052;1.70239;-10.55815;,
 8.52818;1.00971;-10.87072;,
 5.12085;3.40501;-9.39241;,
 4.84587;0.75118;-10.55094;,
 3.69006;2.47120;-9.67382;,
 4.22879;1.05339;-10.36053;,
 3.51132;2.51465;-9.63240;,
 -3.80603;10.49131;0.60224;,
 -4.94534;10.03941;1.00339;,
 -4.63668;10.27763;1.09260;,
 -4.24148;10.50756;1.07852;,
 -8.89055;4.22696;2.93422;,
 -8.69743;6.04341;2.04081;,
 -8.70858;3.08746;2.77577;,
 -7.52663;3.08746;-0.18285;,
 -8.53091;5.96468;1.63972;,
 -7.95547;4.75034;0.50353;,
 -6.18922;8.94804;0.92285;,
 -6.56789;7.79908;0.18428;,
 -8.68814;6.06439;2.04780;,
 -8.69743;6.04341;2.04081;,
 -8.53091;5.96468;1.63972;,
 -1.34363;10.48392;4.52965;,
 -1.44386;10.55209;4.34153;,
 -2.03989;9.92087;4.96688;,
 -1.47564;10.22183;4.87391;,
 -2.47852;10.57380;-0.24534;,
 0.46414;6.68278;-5.67215;,
 -3.80603;10.49131;0.60224;,
 -4.94534;10.03941;1.00339;,
 -6.18922;8.94804;0.92285;,
 -6.56789;7.79908;0.18428;,
 -4.92466;6.30761;-2.26000;,
 0.13896;5.49158;-6.49134;,
 -1.77251;5.04194;-5.55870;,
 -0.55814;11.49477;2.19759;,
 -2.47852;10.57380;-0.24534;,
 -1.70227;11.31206;2.41724;,
 -4.24148;10.50756;1.07852;,
 -3.80603;10.49131;0.60224;,
 3.36825;2.51352;-9.55891;,
 3.69006;2.47120;-9.67382;,
 3.51132;2.51465;-9.63240;,
 5.12085;3.40501;-9.39241;,
 3.69006;2.47120;-9.67382;,
 0.46414;6.68278;-5.67215;,
 0.13896;5.49158;-6.49134;,
 3.36825;2.51352;-9.55891;,
 1.46600;3.56592;-8.29627;,
 -7.95547;4.75034;0.50353;,
 -4.92466;6.30761;-2.26000;,
 -7.52663;3.08746;-0.18285;,
 -5.08164;1.01497;-2.96471;,
 -1.77251;5.04194;-5.55870;,
 -0.60603;0.25143;-7.55135;,
 0.11899;3.03710;-7.74597;,
 0.42783;1.05755;-8.41310;,
 -8.53091;5.96468;1.63972;,
 -6.56789;7.79908;0.18428;,
 -4.92466;6.30761;-2.26000;,
 -7.95547;4.75034;0.50353;,
 -1.77251;5.04194;-5.55870;,
 0.13896;5.49158;-6.49134;,
 1.46600;3.56592;-8.29627;,
 0.11899;3.03710;-7.74597;,
 0.11899;3.03710;-7.74597;,
 1.46600;3.56592;-8.29627;,
 0.42783;1.05755;-8.41310;,
 3.36825;2.51352;-9.55891;,
 4.22879;1.05339;-10.36053;,
 3.51132;2.51465;-9.63240;,
 8.38052;1.70239;-10.55815;,
 5.12085;3.40501;-9.39241;,
 10.95839;3.78330;-5.13923;,
 10.35632;4.48150;-4.12211;,
 7.88568;6.27686;-1.99450;,
 0.46414;6.68278;-5.67215;,
 3.58821;9.23870;0.89936;,
 -2.47852;10.57380;-0.24534;,
 -0.28316;11.47229;2.30837;,
 -0.55814;11.49477;2.19759;,
 7.88568;6.27686;-1.99450;,
 10.03370;4.35123;-3.11281;,
 10.25861;4.18439;-3.29751;,
 10.35632;4.48150;-4.12211;,
 -0.28751;11.11543;3.18664;,
 -0.28316;11.47229;2.30837;,
 -1.34363;10.48392;4.52965;,
 -0.55814;11.49477;2.19759;,
 -1.70227;11.31206;2.41724;,
 -1.44386;10.55209;4.34153;,
 -0.28751;11.11543;3.18664;,
 0.82471;10.24666;3.33578;,
 3.58821;9.23870;0.89936;,
 -0.28316;11.47229;2.30837;,
 1.93454;-0.97230;-6.47680;,
 7.83383;-1.05740;-6.26006;,
 6.64998;-1.06467;-7.08814;,
 0.36041;-1.23710;-3.49286;,
 -2.01365;-1.04166;-2.47663;,
 -2.76498;-1.05642;-0.62763;,
 -1.43114;-1.00210;0.04892;,
 7.20296;-1.08950;-4.41918;,
 4.73703;-1.24307;-3.41329;,
 3.16794;-0.93872;-0.49306;,
 4.09039;-1.24175;-5.38972;,
 1.01300;-1.22442;-1.53769;;
 
 157;
 4;0,1,2,3;,
 3;4,5,6;,
 3;5,7,6;,
 3;7,8,6;,
 3;9,10,11;,
 3;10,12,11;,
 3;12,13,11;,
 3;14,15,16;,
 3;15,17,16;,
 3;17,18,16;,
 4;19,20,21,22;,
 3;23,24,25;,
 3;24,26,25;,
 3;26,27,25;,
 3;27,28,25;,
 3;29,30,31;,
 3;31,30,32;,
 3;30,33,32;,
 4;34,35,36,37;,
 3;38,39,40;,
 3;40,39,41;,
 3;39,42,41;,
 4;43,44,45,46;,
 3;47,48,49;,
 3;48,50,49;,
 3;50,51,49;,
 4;52,53,54,55;,
 3;56,57,58;,
 3;57,59,58;,
 3;59,60,58;,
 3;61,62,63;,
 3;62,64,63;,
 3;64,65,63;,
 3;66,67,68;,
 3;67,69,68;,
 3;69,70,68;,
 3;71,72,73;,
 3;72,74,73;,
 3;73,74,75;,
 3;74,76,75;,
 3;76,77,75;,
 4;78,79,80,81;,
 3;82,83,84;,
 3;83,85,84;,
 3;85,86,84;,
 3;86,87,84;,
 3;84,87,88;,
 3;87,89,88;,
 3;90,91,92;,
 3;92,91,93;,
 3;91,94,93;,
 3;93,94,95;,
 3;94,96,95;,
 3;96,97,95;,
 4;98,99,100,101;,
 3;102,103,104;,
 3;104,103,105;,
 3;103,106,105;,
 3;106,107,105;,
 3;108,109,110;,
 3;109,111,110;,
 3;110,111,112;,
 3;111,113,112;,
 3;114,115,116;,
 3;115,117,116;,
 3;116,117,118;,
 3;117,119,118;,
 3;120,121,122;,
 3;121,123,122;,
 3;123,124,122;,
 3;125,126,127;,
 3;126,128,127;,
 3;128,129,127;,
 3;129,130,127;,
 3;131,132,133;,
 3;132,134,133;,
 3;133,134,135;,
 3;134,136,135;,
 3;136,137,135;,
 4;138,139,140,141;,
 3;142,143,144;,
 3;144,143,145;,
 3;143,146,145;,
 3;146,147,145;,
 3;148,149,150;,
 3;150,149,151;,
 3;149,152,151;,
 4;153,154,155,156;,
 3;157,158,159;,
 3;159,158,160;,
 3;160,158,161;,
 3;161,158,162;,
 3;162,158,163;,
 3;158,164,163;,
 3;164,165,163;,
 3;166,167,168;,
 3;168,167,169;,
 3;167,170,169;,
 3;171,172,173;,
 3;174,175,176;,
 3;176,175,177;,
 3;175,178,177;,
 3;178,179,177;,
 3;180,181,182;,
 3;182,181,183;,
 3;181,184,183;,
 3;183,184,185;,
 3;184,186,185;,
 3;186,187,185;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 3;196,197,198;,
 3;197,199,198;,
 3;198,199,200;,
 3;199,201,200;,
 3;202,203,204;,
 3;204,203,205;,
 3;205,203,206;,
 3;203,207,206;,
 3;206,207,208;,
 3;207,209,208;,
 3;208,209,210;,
 3;209,211,210;,
 4;212,213,214,215;,
 3;216,217,218;,
 3;217,219,218;,
 3;219,220,218;,
 3;220,221,218;,
 4;222,223,224,225;,
 3;226,19,25;,
 4;34,227,228,29;,
 3;226,229,19;,
 3;229,230,19;,
 3;230,16,19;,
 4;230,231,11,16;,
 4;6,11,231,232;,
 4;41,233,227,34;,
 3;41,43,233;,
 3;233,43,234;,
 3;43,235,234;,
 3;43,4,235;,
 3;234,235,236;,
 3;236,235,226;,
 3;235,237,226;,
 3;237,229,226;,
 3;29,228,25;,
 3;228,236,25;,
 3;236,226,25;,
 3;237,232,229;,
 3;229,232,230;,
 3;232,231,230;,
 3;227,233,228;,
 3;233,234,228;,
 3;234,236,228;,
 3;235,4,237;,
 3;237,4,232;,
 3;4,6,232;;
 
 MeshMaterialList {
  11;
  157;
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9;;
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
  97;
  0.122264;-0.860041;0.495360;,
  0.338788;-0.817406;0.465909;,
  0.649102;-0.032370;0.760012;,
  0.333165;-0.250393;0.909013;,
  0.018803;-0.841436;0.540030;,
  0.057221;-0.395113;0.916849;,
  -0.320784;-0.371226;0.871372;,
  -0.496043;-0.853038;0.162072;,
  -0.602118;-0.375558;0.704564;,
  -0.920409;-0.379485;-0.094016;,
  -0.665304;-0.653271;-0.361396;,
  -0.864498;-0.147597;-0.480477;,
  -0.753779;-0.100256;-0.649435;,
  -0.367478;-0.817551;-0.443363;,
  -0.636580;-0.119437;-0.761906;,
  -0.230680;-0.605408;-0.761753;,
  -0.503411;0.039938;-0.863124;,
  -0.336047;0.133769;-0.932297;,
  -0.154188;0.154352;-0.975911;,
  0.249617;-0.789742;-0.560356;,
  -0.096465;0.067112;-0.993071;,
  0.395722;-0.174217;-0.901694;,
  0.709887;-0.704222;-0.011475;,
  0.847049;0.208054;-0.489103;,
  0.705297;-0.622444;0.339292;,
  0.950956;-0.139054;0.276311;,
  0.891205;0.153468;0.426850;,
  0.645878;0.211581;0.733536;,
  0.595471;0.229555;0.769882;,
  0.371956;0.094024;0.923476;,
  -0.798046;0.126144;0.589245;,
  -0.965564;0.081216;0.247164;,
  0.680921;0.674508;-0.285282;,
  0.837874;0.473015;0.272441;,
  0.783280;0.367648;0.501306;,
  0.731590;0.331023;0.595987;,
  0.518419;0.399776;0.755924;,
  0.376696;0.482640;0.790670;,
  0.018636;0.399507;0.916541;,
  0.704263;0.471082;0.531127;,
  0.667423;0.484295;0.565690;,
  0.606662;0.555098;0.569058;,
  -0.117606;-0.004299;0.993051;,
  -0.229824;0.230776;0.945475;,
  -0.309888;0.149233;0.938988;,
  -0.501157;0.302283;0.810843;,
  -0.328343;0.698860;0.635441;,
  -0.298416;0.858293;0.417470;,
  -0.296142;0.928704;0.223178;,
  -0.414897;0.907005;0.072132;,
  -0.534846;0.820479;0.201877;,
  -0.726345;0.601061;0.333389;,
  -0.070333;0.678736;0.731007;,
  0.364018;0.758861;0.540019;,
  0.028368;0.870400;0.491527;,
  -0.886324;0.454580;0.088241;,
  -0.940731;0.176359;-0.289694;,
  -0.593033;0.749418;-0.294422;,
  -0.672915;0.676135;-0.300045;,
  0.426904;0.592094;-0.683504;,
  -0.286370;0.310968;-0.906251;,
  -0.151524;0.498788;-0.853376;,
  0.069631;0.701024;-0.709730;,
  -0.411300;0.749862;-0.518207;,
  -0.869289;0.151241;-0.470598;,
  -0.800465;0.099330;-0.591091;,
  -0.673172;0.495830;-0.548627;,
  -0.033276;0.903555;-0.427179;,
  -0.232902;0.701562;-0.673475;,
  -0.335211;0.566559;-0.752758;,
  -0.620448;0.277896;-0.733361;,
  -0.620987;0.347334;-0.702662;,
  -0.018899;0.999807;0.005323;,
  0.318205;0.708085;0.630366;,
  -0.395684;0.371435;-0.839922;,
  -0.584000;0.225140;-0.779908;,
  0.221005;0.975260;0.005091;,
  -0.053836;-0.989865;-0.131411;,
  0.036913;-0.988052;0.149638;,
  -0.016567;-0.987867;0.154417;,
  -0.133340;-0.990308;0.038866;,
  -0.169952;-0.978206;-0.119288;,
  -0.089101;-0.992706;-0.081214;,
  0.055124;-0.993021;0.104267;,
  0.031668;-0.993008;-0.113720;,
  0.160023;-0.986642;-0.030502;,
  0.152122;-0.983119;0.101663;,
  0.070121;-0.993686;0.087581;,
  -0.060559;-0.995116;-0.077957;,
  -0.503618;0.775765;0.380207;,
  -0.543207;0.751853;0.373690;,
  0.705197;0.391213;-0.591312;,
  0.581130;0.556302;-0.593983;,
  -0.354592;0.378672;-0.854910;,
  0.259290;0.862882;-0.433825;,
  0.264009;0.857736;-0.441122;,
  0.274280;0.833344;-0.479904;;
  157;
  4;0,1,2,3;,
  3;0,3,4;,
  3;3,5,4;,
  3;5,6,4;,
  3;4,6,7;,
  3;6,8,7;,
  3;8,9,7;,
  3;7,9,10;,
  3;9,11,10;,
  3;11,12,10;,
  4;13,10,12,14;,
  3;13,14,15;,
  3;14,16,15;,
  3;16,17,15;,
  3;17,18,15;,
  3;19,15,21;,
  3;21,15,20;,
  3;15,18,20;,
  4;22,19,21,23;,
  3;23,25,22;,
  3;22,25,24;,
  3;25,26,24;,
  4;1,24,26,2;,
  3;2,27,3;,
  3;27,28,3;,
  3;28,29,3;,
  4;9,8,30,31;,
  3;25,32,26;,
  3;32,33,26;,
  3;33,34,26;,
  3;26,34,2;,
  3;34,35,2;,
  3;35,27,2;,
  3;28,36,29;,
  3;36,37,29;,
  3;37,38,29;,
  3;35,39,27;,
  3;39,40,27;,
  3;27,40,28;,
  3;40,41,28;,
  3;41,36,28;,
  4;42,5,3,29;,
  3;5,42,6;,
  3;42,43,6;,
  3;43,44,6;,
  3;44,45,6;,
  3;6,45,8;,
  3;45,30,8;,
  3;47,48,46;,
  3;46,48,89;,
  3;48,49,89;,
  3;89,49,90;,
  3;49,50,45;,
  3;50,51,45;,
  4;38,43,42,29;,
  3;41,53,36;,
  3;36,53,37;,
  3;53,54,37;,
  3;54,52,37;,
  3;37,52,38;,
  3;52,46,38;,
  3;38,46,43;,
  3;46,44,43;,
  3;45,51,30;,
  3;51,55,30;,
  3;30,55,31;,
  3;55,56,31;,
  3;50,57,51;,
  3;57,58,51;,
  3;58,55,51;,
  3;21,91,23;,
  3;91,59,23;,
  3;59,32,23;,
  3;32,92,23;,
  3;59,20,62;,
  3;20,18,62;,
  3;62,18,61;,
  3;18,17,61;,
  3;17,60,61;,
  4;63,57,50,49;,
  3;31,56,9;,
  3;9,56,11;,
  3;56,64,11;,
  3;64,65,11;,
  3;58,66,55;,
  3;55,66,56;,
  3;66,64,56;,
  4;54,47,46,52;,
  3;67,68,63;,
  3;63,68,57;,
  3;57,68,58;,
  3;58,68,66;,
  3;66,68,71;,
  3;68,69,71;,
  3;69,70,71;,
  3;72,67,48;,
  3;48,67,49;,
  3;67,63,49;,
  3;73,73,73;,
  3;62,61,68;,
  3;68,61,69;,
  3;61,93,69;,
  3;93,74,69;,
  3;65,71,11;,
  3;11,71,12;,
  3;71,70,12;,
  3;12,70,14;,
  3;70,75,14;,
  3;75,16,14;,
  4;64,66,71,65;,
  4;70,69,74,75;,
  3;75,74,16;,
  3;74,93,16;,
  3;16,93,17;,
  3;93,60,17;,
  3;59,62,32;,
  3;32,62,94;,
  3;94,62,95;,
  3;62,68,95;,
  3;95,68,96;,
  3;68,67,96;,
  3;96,67,76;,
  3;67,72,76;,
  4;39,35,34,33;,
  3;53,76,54;,
  3;76,72,54;,
  3;72,48,54;,
  3;48,47,54;,
  4;53,41,40,76;,
  3;77,13,15;,
  4;22,85,84,19;,
  3;77,82,13;,
  3;82,81,13;,
  3;81,10,13;,
  4;81,80,7,10;,
  4;4,7,80,79;,
  4;24,86,85,22;,
  3;24,1,86;,
  3;86,1,87;,
  3;1,78,87;,
  3;1,0,78;,
  3;87,78,88;,
  3;88,78,77;,
  3;78,83,77;,
  3;83,82,77;,
  3;19,84,15;,
  3;84,88,15;,
  3;88,77,15;,
  3;83,79,82;,
  3;82,79,81;,
  3;79,80,81;,
  3;85,86,84;,
  3;86,87,84;,
  3;87,88,84;,
  3;78,0,83;,
  3;83,0,79;,
  3;0,4,79;;
 }
 MeshTextureCoords {
  238;
  0.290530;0.381648;,
  0.291462;0.482762;,
  0.352205;0.471133;,
  0.352205;0.337120;,
  0.364017;0.221194;,
  0.292293;0.246821;,
  0.364017;0.293535;,
  0.290530;0.280586;,
  0.328887;0.326443;,
  0.577492;0.683966;,
  0.566298;0.729478;,
  0.629720;0.696298;,
  0.599341;0.775592;,
  0.629720;0.775614;,
  0.675553;0.623974;,
  0.742898;0.666822;,
  0.677700;0.542140;,
  0.742898;0.610125;,
  0.700028;0.548005;,
  0.072492;0.175456;,
  0.060568;0.279105;,
  0.080491;0.290804;,
  0.080491;0.175953;,
  0.561875;0.064671;,
  0.553909;0.064121;,
  0.561875;0.171276;,
  0.538844;0.087603;,
  0.539458;0.163601;,
  0.545255;0.174875;,
  0.362347;0.119284;,
  0.362347;0.039576;,
  0.359504;0.120081;,
  0.340346;0.107059;,
  0.345364;0.041313;,
  0.176670;0.443526;,
  0.183018;0.498198;,
  0.185953;0.498058;,
  0.185953;0.441753;,
  0.631899;0.133546;,
  0.579617;0.178568;,
  0.640733;0.136823;,
  0.640733;0.213305;,
  0.578983;0.213637;,
  0.735644;0.764858;,
  0.734361;0.875033;,
  0.795757;0.881777;,
  0.795757;0.749073;,
  0.185953;0.508876;,
  0.163316;0.515980;,
  0.185953;0.643005;,
  0.127361;0.564246;,
  0.127476;0.653130;,
  0.178376;0.051364;,
  0.178375;0.020891;,
  0.148040;0.021717;,
  0.157715;0.050623;,
  0.902242;0.230905;,
  0.888807;0.237477;,
  0.902242;0.265988;,
  0.875322;0.257831;,
  0.881107;0.272416;,
  0.908252;0.527158;,
  0.888373;0.536700;,
  0.908252;0.659851;,
  0.885360;0.541847;,
  0.885599;0.666822;,
  0.823825;0.905405;,
  0.763096;0.954717;,
  0.823825;0.994306;,
  0.761879;0.986456;,
  0.771524;0.994661;,
  0.558589;0.666822;,
  0.568326;0.612636;,
  0.492183;0.561018;,
  0.568326;0.506432;,
  0.500575;0.501375;,
  0.549638;0.441092;,
  0.531519;0.429446;,
  0.426288;0.059635;,
  0.430895;0.121116;,
  0.464045;0.127474;,
  0.464045;0.067965;,
  0.429286;0.781437;,
  0.443260;0.721430;,
  0.369919;0.790077;,
  0.445727;0.695692;,
  0.436794;0.689296;,
  0.382817;0.689296;,
  0.345211;0.738291;,
  0.355834;0.709808;,
  0.579738;0.450283;,
  0.607687;0.474614;,
  0.578983;0.431282;,
  0.604305;0.375017;,
  0.656026;0.453044;,
  0.647596;0.342854;,
  0.660684;0.446388;,
  0.660684;0.350049;,
  0.137383;0.068038;,
  0.091231;0.092801;,
  0.098840;0.117527;,
  0.137383;0.120446;,
  0.199017;0.062059;,
  0.223879;0.057900;,
  0.197077;0.040580;,
  0.213341;0.013307;,
  0.223879;0.025484;,
  0.220953;0.017988;,
  0.811650;0.125125;,
  0.820083;0.128074;,
  0.806775;0.113431;,
  0.821773;0.116710;,
  0.812777;0.061316;,
  0.821773;0.054991;,
  0.944846;0.307173;,
  0.935463;0.318856;,
  0.971092;0.328620;,
  0.934686;0.359738;,
  0.971092;0.359117;,
  0.934988;0.360039;,
  0.914911;0.677942;,
  0.909799;0.682858;,
  0.914911;0.774284;,
  0.892706;0.706822;,
  0.874149;0.775107;,
  0.780811;0.488601;,
  0.803697;0.491449;,
  0.764707;0.434712;,
  0.815017;0.483696;,
  0.815017;0.370717;,
  0.801138;0.376085;,
  0.864666;0.275464;,
  0.854563;0.266120;,
  0.864666;0.344116;,
  0.818352;0.321178;,
  0.836634;0.356787;,
  0.817907;0.333857;,
  0.835808;0.360039;,
  0.183288;0.399432;,
  0.183288;0.376481;,
  0.179233;0.382326;,
  0.176670;0.390050;,
  0.766736;0.677878;,
  0.734361;0.693918;,
  0.787069;0.681698;,
  0.787069;0.738396;,
  0.735763;0.701646;,
  0.757424;0.724222;,
  0.963578;0.032283;,
  0.943592;0.047621;,
  0.963578;0.103078;,
  0.963320;0.103417;,
  0.956021;0.100553;,
  0.715467;0.712185;,
  0.719072;0.713863;,
  0.719072;0.694823;,
  0.712938;0.704544;,
  0.578983;0.520481;,
  0.595124;0.649332;,
  0.596042;0.498218;,
  0.615721;0.486474;,
  0.645124;0.485292;,
  0.664896;0.500906;,
  0.664896;0.559658;,
  0.614821;0.666822;,
  0.643765;0.641218;,
  0.329690;0.120081;,
  0.329690;0.062404;,
  0.311297;0.110039;,
  0.290530;0.061238;,
  0.301842;0.059358;,
  0.363387;0.482762;,
  0.363387;0.476635;,
  0.362862;0.479949;,
  0.844001;0.760726;,
  0.813982;0.767409;,
  0.844001;0.881777;,
  0.821841;0.867551;,
  0.811095;0.772811;,
  0.806414;0.817303;,
  0.509293;0.994661;,
  0.555641;0.931897;,
  0.484424;0.973161;,
  0.466321;0.899844;,
  0.555641;0.847636;,
  0.483693;0.786320;,
  0.534882;0.788572;,
  0.504018;0.767223;,
  0.870415;0.791561;,
  0.854658;0.843597;,
  0.899226;0.881777;,
  0.899226;0.803701;,
  0.746346;0.050732;,
  0.716097;0.074776;,
  0.722437;0.126963;,
  0.746346;0.113351;,
  0.492129;0.088532;,
  0.482455;0.114322;,
  0.528187;0.098871;,
  0.501653;0.154715;,
  0.528187;0.174875;,
  0.501632;0.157578;,
  0.314658;0.994661;,
  0.334554;0.928968;,
  0.208846;0.955467;,
  0.201274;0.932251;,
  0.199167;0.866070;,
  0.334554;0.807946;,
  0.206168;0.760102;,
  0.290403;0.685856;,
  0.228876;0.679963;,
  0.233548;0.677500;,
  0.183125;0.135390;,
  0.169260;0.188669;,
  0.169101;0.194637;,
  0.183125;0.201629;,
  0.939359;0.398668;,
  0.937190;0.415398;,
  0.961297;0.374843;,
  0.941804;0.417970;,
  0.962627;0.415701;,
  0.962627;0.378596;,
  0.929492;0.581688;,
  0.918909;0.604610;,
  0.946241;0.666822;,
  0.946241;0.583424;,
  0.214530;0.301698;,
  0.299089;0.457235;,
  0.341358;0.387213;,
  0.362448;0.437497;,
  0.539814;0.537418;,
  0.504576;0.570977;,
  0.443323;0.476569;,
  0.430687;0.384005;,
  0.442134;0.534294;,
  0.590606;0.635950;,
  0.292176;0.404108;,
  0.512349;0.571169;;
 }
}
