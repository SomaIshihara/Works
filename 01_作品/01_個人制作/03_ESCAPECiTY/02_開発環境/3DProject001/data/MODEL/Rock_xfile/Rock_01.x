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
 134;
 30.31975;-5.57725;-55.79475;,
 25.63437;45.21538;-46.54800;,
 53.26912;-1.41612;-23.20100;,
 45.09050;46.04163;-31.43725;,
 55.58763;32.44200;-22.73100;,
 60.81713;38.88312;-3.54412;,
 54.51787;-1.16400;11.75138;,
 64.76225;28.63613;6.65388;,
 64.16700;15.04588;5.07850;,
 62.70438;12.20550;13.52488;,
 62.70438;12.20550;13.52488;,
 62.83688;26.11000;18.26150;,
 54.51787;-1.16400;11.75138;,
 45.15738;45.49375;31.02950;,
 35.25850;-5.99238;45.61225;,
 34.68937;46.59688;44.02675;,
 -6.69012;-3.73762;58.42438;,
 23.42737;47.64163;47.19575;,
 7.75463;39.75900;53.23612;,
 -6.10025;18.50600;61.07038;,
 -49.03287;-5.15675;51.64362;,
 -50.12475;3.49713;53.12300;,
 -56.25738;19.13612;47.24750;,
 -76.49825;-5.22362;23.36900;,
 -67.95700;19.10750;34.01613;,
 -77.05625;10.08387;23.58225;,
 -78.87625;-5.61925;-14.30788;,
 -77.34250;14.26112;18.69587;,
 -78.15625;18.19587;-5.99750;,
 -79.25700;-2.39825;-14.38162;,
 -53.44913;-4.48138;-46.07762;,
 -78.87625;-5.61925;-14.30788;,
 -79.25700;-2.39825;-14.38162;,
 -54.23012;5.19125;-46.98700;,
 -25.01163;45.59187;-49.51600;,
 -20.24787;45.72975;-51.65563;,
 -10.02650;38.10975;-62.72350;,
 -12.64162;-7.07050;-74.80312;,
 3.82737;45.34525;-51.57725;,
 32.94212;57.40025;26.05125;,
 27.28500;55.82412;34.67275;,
 0.55300;52.84087;-43.80225;,
 14.10962;51.64062;-41.40400;,
 16.09688;57.54900;-34.67438;,
 11.67050;63.70837;-35.42313;,
 28.45687;58.89150;-23.30050;,
 18.15425;64.68850;-30.35963;,
 24.58575;63.56563;-23.27837;,
 -16.28775;60.29813;-41.09663;,
 0.26625;68.86126;-37.29075;,
 -12.62313;69.33250;-37.62862;,
 33.30962;61.08275;-12.59712;,
 52.14825;49.83663;-11.04588;,
 46.54875;51.03550;-22.49413;,
 26.15088;69.04337;-4.39462;,
 18.05612;67.66512;-21.96963;,
 25.42825;67.49413;13.79825;,
 9.52913;70.85487;-26.03287;,
 14.80312;69.08563;19.53112;,
 -4.33000;75.82912;-20.94038;,
 3.19238;73.15113;18.85962;,
 -8.73500;76.64100;-12.76200;,
 -10.02237;76.79125;6.68662;,
 28.38488;66.69887;-10.72925;,
 16.40237;67.02200;-28.60763;,
 11.07800;70.45987;-29.98925;,
 1.28625;73.15625;-33.05000;,
 26.15088;69.04337;-4.39462;,
 18.05612;67.66512;-21.96963;,
 13.17338;63.19662;31.07337;,
 11.11500;65.85313;27.35787;,
 6.75400;67.37263;27.16113;,
 -61.57800;34.44925;-9.81062;,
 -32.55750;46.97325;-38.80213;,
 -78.15625;18.19587;-5.99750;,
 -58.97763;40.86900;25.38312;,
 -59.61775;40.38662;24.49525;,
 -66.22675;30.38600;26.22912;,
 -53.33212;46.45300;9.96262;,
 -61.57800;34.44925;-9.81062;,
 12.58700;51.14637;46.12137;,
 9.07875;63.35238;31.47800;,
 7.53237;58.39425;36.14487;,
 5.04488;64.80113;29.57500;,
 9.52913;70.85487;-26.03287;,
 -9.21750;77.52637;-24.94200;,
 -15.02725;75.33088;-15.56288;,
 -58.36500;40.83737;25.99863;,
 -59.61775;40.38662;24.49525;,
 -58.97763;40.86900;25.38312;,
 -32.85462;57.06100;19.57463;,
 -36.13650;61.46362;11.06975;,
 -43.75612;49.80275;26.47025;,
 -58.36500;40.83737;25.99863;,
 -3.71262;62.61137;30.22413;,
 -18.75412;63.83350;24.92063;,
 -27.77975;56.47450;26.52450;,
 -42.19763;47.24587;35.81775;,
 -4.33000;75.82912;-20.94038;,
 -8.26925;75.75438;-31.58725;,
 -9.21750;77.52637;-24.94200;,
 -23.52638;70.92500;14.00200;,
 -28.82475;70.23625;4.71025;,
 -22.57437;53.15087;-44.47813;,
 -8.26925;75.75438;-31.58725;,
 -12.62313;69.33250;-37.62862;,
 -16.28775;60.29813;-41.09663;,
 -22.57437;53.15087;-44.47813;,
 -32.55750;46.97325;-38.80213;,
 54.51787;-1.16400;11.75138;,
 35.25850;-5.99238;45.61225;,
 24.99900;-9.83950;-7.54513;,
 -31.80337;-12.17587;34.75775;,
 -6.60200;-11.85675;45.49212;,
 -6.69012;-3.73762;58.42438;,
 -49.03287;-5.15675;51.64362;,
 -44.75150;-12.36150;-16.51850;,
 -41.04000;-12.04437;-7.40112;,
 -76.49825;-5.22362;23.36900;,
 -78.87625;-5.61925;-14.30788;,
 30.31975;-5.57725;-55.79475;,
 53.26912;-1.41612;-23.20100;,
 11.05438;-11.73800;-21.33038;,
 60.81713;38.88312;-3.54412;,
 52.14825;49.83663;-11.04588;,
 64.76225;28.63613;6.65388;,
 33.30962;61.08275;-12.59712;,
 28.38488;66.69887;-10.72925;,
 62.83688;26.11000;18.26150;,
 -12.64162;-7.07050;-74.80312;,
 -13.99462;-11.45613;-18.96637;,
 -53.44913;-4.48138;-46.07762;,
 -39.31487;-12.24687;-29.29962;,
 -30.10037;-11.54675;-2.07250;;
 
 174;
 3;0,1,2;,
 3;1,3,2;,
 3;3,4,2;,
 3;4,5,2;,
 3;2,5,6;,
 3;5,7,8;,
 3;5,8,6;,
 3;8,9,6;,
 3;10,11,12;,
 3;11,13,12;,
 3;12,13,14;,
 3;13,15,14;,
 3;14,15,16;,
 3;15,17,16;,
 3;17,18,16;,
 3;18,19,16;,
 4;20,16,19,21;,
 3;21,22,20;,
 3;20,22,23;,
 3;22,24,23;,
 3;24,25,23;,
 3;23,25,26;,
 3;25,27,26;,
 3;27,28,26;,
 3;28,29,26;,
 4;30,31,32,33;,
 3;34,35,33;,
 3;35,36,33;,
 3;33,36,30;,
 3;36,37,30;,
 3;37,36,0;,
 3;0,36,1;,
 3;36,38,1;,
 4;15,13,39,40;,
 4;1,38,41,42;,
 3;43,44,45;,
 3;44,46,45;,
 3;46,47,45;,
 3;42,41,43;,
 3;43,41,44;,
 3;41,48,44;,
 3;44,48,49;,
 3;48,50,49;,
 4;51,52,53,45;,
 3;54,55,56;,
 3;55,57,56;,
 3;56,57,58;,
 3;57,59,58;,
 3;58,59,60;,
 3;59,61,60;,
 3;61,62,60;,
 4;47,63,51,45;,
 3;44,49,46;,
 3;46,49,64;,
 3;64,49,65;,
 3;49,66,65;,
 3;47,46,63;,
 3;46,64,63;,
 3;63,64,67;,
 3;64,68,67;,
 3;39,56,40;,
 3;56,58,40;,
 3;40,58,69;,
 3;58,70,69;,
 4;58,60,71,70;,
 3;72,73,74;,
 3;74,73,32;,
 3;73,34,32;,
 3;34,33,32;,
 3;75,76,77;,
 3;76,78,77;,
 3;77,78,27;,
 3;78,79,27;,
 3;79,28,27;,
 3;15,40,17;,
 3;40,69,17;,
 3;17,69,80;,
 3;69,81,80;,
 3;81,82,80;,
 3;69,70,81;,
 3;70,71,81;,
 3;71,83,81;,
 4;65,84,68,64;,
 4;85,86,61,59;,
 3;87,88,89;,
 3;90,91,92;,
 3;91,78,92;,
 3;92,78,93;,
 3;78,76,93;,
 3;80,82,18;,
 3;18,82,19;,
 3;82,94,19;,
 3;19,94,21;,
 3;94,95,21;,
 3;95,96,21;,
 3;96,97,21;,
 3;97,22,21;,
 4;81,83,94,82;,
 4;96,90,92,97;,
 3;97,92,22;,
 3;92,93,22;,
 3;22,93,24;,
 3;93,75,24;,
 3;75,77,24;,
 3;65,66,84;,
 3;84,66,98;,
 3;66,99,98;,
 3;99,100,98;,
 4;66,49,50,99;,
 3;62,61,101;,
 3;61,86,101;,
 3;86,102,101;,
 3;71,60,83;,
 3;83,60,94;,
 3;60,62,94;,
 3;94,62,95;,
 3;62,101,95;,
 3;95,101,96;,
 3;96,101,90;,
 3;101,102,90;,
 3;102,91,90;,
 4;103,35,34,73;,
 3;38,36,41;,
 3;41,36,48;,
 3;36,35,48;,
 3;35,103,48;,
 3;102,86,91;,
 3;86,85,91;,
 3;91,85,78;,
 3;85,104,78;,
 3;104,105,78;,
 3;105,106,78;,
 3;78,106,79;,
 3;106,107,79;,
 3;107,108,79;,
 3;109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,111,122;,
 3;123,124,125;,
 3;125,124,11;,
 3;124,126,11;,
 3;11,126,13;,
 3;126,127,13;,
 3;127,54,13;,
 3;54,56,13;,
 3;56,39,13;,
 3;3,53,4;,
 3;4,53,5;,
 3;53,52,5;,
 3;3,1,53;,
 3;53,1,45;,
 3;1,42,45;,
 3;42,43,45;,
 4;8,7,128,9;,
 3;17,80,18;,
 4;24,77,27,25;,
 3;120,122,129;,
 3;122,130,129;,
 3;129,130,131;,
 3;130,132,131;,
 4;111,110,114,113;,
 3;121,109,111;,
 4;131,132,116,119;,
 3;112,115,133;,
 3;133,115,117;,
 3;115,118,117;,
 3;130,133,132;,
 3;133,117,132;,
 3;117,116,132;,
 3;111,113,122;,
 3;122,113,130;,
 3;113,112,130;,
 3;112,133,130;;
 
 MeshMaterialList {
  11;
  174;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
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
  120;
  0.852369;-0.024442;-0.522369;,
  0.534474;0.204791;-0.819999;,
  0.418202;0.580047;-0.699037;,
  0.667715;0.314687;-0.674633;,
  0.862684;0.192936;-0.467495;,
  0.866070;-0.484409;0.123572;,
  0.950464;0.123363;-0.285305;,
  0.976147;0.216322;0.018495;,
  0.975498;-0.203703;-0.083117;,
  0.951812;-0.299939;0.063957;,
  0.684110;0.010913;0.729298;,
  0.310214;-0.309200;0.898979;,
  0.786341;0.498064;0.365515;,
  0.474800;0.369888;0.798591;,
  0.290226;-0.038921;0.956166;,
  0.251443;0.515992;0.818858;,
  0.374844;0.137112;0.916893;,
  -0.019313;0.251207;0.967741;,
  -0.428975;-0.757873;0.491538;,
  -0.240253;0.310685;0.919649;,
  -0.835581;-0.048929;0.547184;,
  -0.762635;0.242339;0.599717;,
  -0.730990;0.315495;0.605075;,
  -0.946506;0.082958;0.311839;,
  -0.998432;-0.051477;-0.022014;,
  -0.907880;0.408802;0.092927;,
  -0.923863;0.360379;-0.128855;,
  -0.924005;-0.100780;0.368860;,
  -0.552810;0.007370;-0.833275;,
  -0.584195;0.190411;-0.788961;,
  -0.090027;0.262104;-0.960831;,
  -0.610731;0.447632;-0.653172;,
  -0.423591;0.492444;-0.760309;,
  -0.051227;0.466017;-0.883292;,
  0.154385;0.741542;-0.652902;,
  0.524300;0.774545;0.353820;,
  0.350671;0.800819;0.485509;,
  0.213713;0.630826;-0.745912;,
  0.282423;0.724703;-0.628524;,
  0.543912;0.614412;-0.571540;,
  0.459106;0.474943;-0.750767;,
  0.412761;0.339138;-0.845348;,
  0.550148;0.614675;-0.565254;,
  0.622350;0.657419;-0.424829;,
  -0.264054;0.614830;-0.743142;,
  -0.387199;0.629925;-0.673254;,
  0.289964;0.522273;-0.801967;,
  0.649116;0.760232;-0.026383;,
  0.636318;0.757163;0.147657;,
  0.645186;0.642104;-0.414049;,
  0.353037;0.935010;-0.033468;,
  0.166683;0.985108;-0.042180;,
  0.323988;0.945733;-0.024927;,
  0.272470;0.961494;-0.035901;,
  -0.038391;0.998865;0.028177;,
  -0.133848;0.927828;0.348166;,
  0.062179;0.932247;0.356439;,
  0.296630;0.915054;0.273290;,
  0.359565;0.915406;0.180958;,
  0.625580;0.747926;-0.221939;,
  0.419172;0.826808;-0.375079;,
  0.275153;0.898297;-0.342568;,
  0.442005;0.792428;-0.420344;,
  0.212633;0.826494;0.521243;,
  0.197926;0.808122;0.554765;,
  0.049711;0.788382;0.613175;,
  -0.684069;0.701462;-0.200001;,
  -0.655651;0.534926;-0.532894;,
  -0.816992;0.536177;0.212223;,
  -0.690723;0.527566;0.494547;,
  -0.730684;0.676448;0.092297;,
  -0.703038;0.704398;-0.097775;,
  -0.006934;0.760435;0.649377;,
  -0.316140;0.637646;0.702469;,
  -0.077355;0.697594;0.712306;,
  -0.142002;0.730955;0.667488;,
  -0.261856;0.952653;-0.154545;,
  -0.354588;0.933868;-0.046454;,
  0.680897;0.314157;-0.661578;,
  -0.518578;0.768777;0.374245;,
  -0.475618;0.751518;0.457174;,
  -0.603596;0.779442;0.167754;,
  -0.209291;0.684617;0.698210;,
  -0.233459;0.689629;0.685499;,
  -0.290450;0.657299;0.695411;,
  0.214334;0.325453;0.920946;,
  -0.145815;0.920976;-0.361305;,
  -0.478270;0.810493;0.338170;,
  -0.412810;0.849739;0.327919;,
  -0.528392;0.674454;-0.515668;,
  0.208182;-0.976614;0.053713;,
  0.025610;-0.987698;0.154260;,
  -0.135402;-0.985788;0.099440;,
  0.080947;-0.995402;-0.051216;,
  -0.040091;-0.997287;0.061739;,
  -0.133505;-0.990529;-0.032074;,
  0.022469;-0.988698;-0.148226;,
  0.020147;-0.993707;-0.110187;,
  -0.074345;-0.997056;0.018766;,
  -0.063482;-0.347349;-0.935584;,
  0.310203;-0.309198;0.898983;,
  -0.751652;0.285694;-0.594473;,
  -0.558606;0.695943;0.451244;,
  -0.483573;0.588493;0.647945;,
  -0.521981;0.573138;0.631702;,
  0.032270;0.362576;0.931396;,
  -0.613379;0.725798;0.311421;,
  -0.815192;0.339007;-0.469612;,
  -0.792162;0.478648;-0.378649;,
  0.271543;-0.962272;0.017233;,
  0.204116;-0.965982;0.158791;,
  0.006138;-0.927356;0.374131;,
  -0.140548;-0.986538;0.083597;,
  -0.225424;-0.972733;-0.054540;,
  0.162523;-0.981700;-0.099255;,
  0.259142;-0.965110;-0.037510;,
  0.423888;0.715658;0.555115;,
  0.792242;0.555798;0.251877;,
  -0.016067;-0.995294;-0.095557;,
  -0.045179;-0.955088;-0.292859;;
  174;
  3;1,2,0;,
  3;2,3,0;,
  3;3,4,0;,
  3;4,6,0;,
  3;0,6,5;,
  3;6,7,8;,
  3;99,99,99;,
  3;8,9,5;,
  3;100,11,11;,
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
  4;28,24,101,29;,
  3;31,32,29;,
  3;32,33,29;,
  3;29,33,28;,
  3;33,30,28;,
  3;30,33,1;,
  3;1,33,2;,
  3;33,34,2;,
  4;13,12,35,36;,
  4;2,34,37,38;,
  3;40,41,39;,
  3;41,42,39;,
  3;42,43,39;,
  3;38,37,40;,
  3;40,37,41;,
  3;37,44,41;,
  3;41,44,46;,
  3;44,45,46;,
  4;47,48,49,39;,
  3;50,51,58;,
  3;51,52,58;,
  3;58,52,57;,
  3;52,53,57;,
  3;57,53,56;,
  3;53,54,56;,
  3;54,55,56;,
  4;43,59,47,39;,
  3;41,46,42;,
  3;42,46,60;,
  3;60,46,62;,
  3;46,61,62;,
  3;43,42,59;,
  3;42,60,59;,
  3;59,60,50;,
  3;60,51,50;,
  3;35,58,36;,
  3;58,57,36;,
  3;36,57,64;,
  3;57,63,64;,
  4;57,56,65,63;,
  3;66,67,26;,
  3;26,67,101;,
  3;67,31,101;,
  3;31,29,101;,
  3;69,70,68;,
  3;70,71,68;,
  3;68,71,25;,
  3;71,66,25;,
  3;66,26,25;,
  3;13,36,15;,
  3;36,64,15;,
  3;15,64,74;,
  3;64,72,74;,
  3;72,73,74;,
  3;64,63,72;,
  3;63,65,72;,
  3;65,75,72;,
  4;62,52,51,60;,
  4;76,77,54,53;,
  3;78,78,78;,
  3;80,81,79;,
  3;81,71,79;,
  3;79,71,102;,
  3;71,70,102;,
  3;74,73,103;,
  3;103,73,104;,
  3;73,82,17;,
  3;17,82,19;,
  3;82,83,19;,
  3;83,84,19;,
  3;84,85,19;,
  3;85,105,19;,
  4;72,75,82,73;,
  4;84,80,79,106;,
  3;106,79,21;,
  3;79,102,21;,
  3;21,102,22;,
  3;102,69,22;,
  3;69,68,22;,
  3;62,61,52;,
  3;52,61,53;,
  3;61,86,53;,
  3;86,76,53;,
  4;61,46,45,86;,
  3;55,54,88;,
  3;54,77,88;,
  3;77,87,88;,
  3;65,56,75;,
  3;75,56,82;,
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
  3;107,107,107;,
  3;77,108,81;,
  3;81,76,71;,
  3;76,86,71;,
  3;86,45,71;,
  3;45,44,71;,
  3;71,44,66;,
  3;44,89,66;,
  3;89,67,66;,
  3;109,110,90;,
  4;92,91,111,18;,
  4;95,94,112,113;,
  4;114,115,90,93;,
  3;116,48,116;,
  3;7,48,117;,
  3;48,47,117;,
  3;117,47,12;,
  3;47,59,12;,
  3;59,50,12;,
  3;50,58,12;,
  3;58,35,12;,
  3;3,49,4;,
  3;4,49,6;,
  3;49,48,6;,
  3;3,2,49;,
  3;49,2,39;,
  3;2,38,39;,
  3;38,40,39;,
  4;8,7,117,9;,
  3;15,74,16;,
  4;22,68,25,23;,
  3;114,93,118;,
  3;93,97,118;,
  3;118,97,119;,
  3;97,96,119;,
  4;90,110,111,91;,
  3;115,5,90;,
  4;119,96,95,113;,
  3;92,18,98;,
  3;98,18,94;,
  3;18,112,94;,
  3;97,98,96;,
  3;98,94,96;,
  3;94,95,96;,
  3;90,91,93;,
  3;93,91,97;,
  3;91,92,97;,
  3;92,98,97;;
 }
 MeshTextureCoords {
  134;
  0.501047;0.293875;,
  0.679370;0.223568;,
  0.500751;0.151904;,
  0.656299;0.133694;,
  0.601000;0.101654;,
  0.631516;0.036957;,
  0.539116;0.072360;,
  0.602826;0.016384;,
  0.560244;0.038586;,
  0.564437;0.028102;,
  0.622695;0.519265;,
  0.598837;0.525211;,
  0.669860;0.533122;,
  0.619279;0.576892;,
  0.799176;0.521823;,
  0.668619;0.585380;,
  0.916128;0.629452;,
  0.698352;0.615291;,
  0.766091;0.643333;,
  0.866305;0.647342;,
  1.000000;0.772132;,
  0.984576;0.782313;,
  0.947326;0.830145;,
  1.000000;0.911859;,
  0.944725;0.891963;,
  0.964359;0.930268;,
  0.923755;0.991725;,
  0.944100;0.945279;,
  0.882217;1.000000;,
  0.916588;0.996644;,
  0.701108;0.513199;,
  0.790551;0.519265;,
  0.801283;0.516476;,
  0.731738;0.505267;,
  0.789231;0.375662;,
  0.776642;0.366372;,
  0.717642;0.370398;,
  0.569590;0.460848;,
  0.722243;0.297213;,
  0.606791;0.637656;,
  0.642259;0.636725;,
  0.761677;0.280422;,
  0.730717;0.237622;,
  0.752381;0.209903;,
  0.780388;0.216556;,
  0.742305;0.147941;,
  0.774914;0.185660;,
  0.765373;0.153191;,
  0.825174;0.313793;,
  0.819434;0.247031;,
  0.849038;0.284364;,
  0.750702;0.108027;,
  0.675965;0.064440;,
  0.678857;0.103862;,
  0.526937;0.730635;,
  0.510001;0.788191;,
  0.572210;0.695921;,
  0.512497;0.826028;,
  0.604793;0.719505;,
  0.542696;0.864645;,
  0.619521;0.761304;,
  0.568546;0.863361;,
  0.613694;0.829863;,
  0.781151;0.111140;,
  0.788041;0.183993;,
  0.808878;0.198026;,
  0.835371;0.229516;,
  0.800669;0.100935;,
  0.794033;0.164051;,
  0.648126;0.695631;,
  0.638131;0.712166;,
  0.643803;0.727749;,
  0.881516;0.409272;,
  0.822582;0.372520;,
  0.872292;0.469283;,
  0.852488;0.905169;,
  0.853160;0.908331;,
  0.896240;0.914275;,
  0.792366;0.923774;,
  0.796889;0.974189;,
  0.711833;0.654857;,
  0.657845;0.707703;,
  0.683653;0.697920;,
  0.659215;0.725498;,
  0.818097;0.193439;,
  0.540781;0.889424;,
  0.579764;0.886808;,
  0.000890;0.492357;,
  0.000890;0.484915;,
  0.000000;0.489334;,
  0.741464;0.853591;,
  0.719465;0.885137;,
  0.798818;0.865899;,
  0.852536;0.902044;,
  0.685686;0.748918;,
  0.704923;0.807134;,
  0.746707;0.823764;,
  0.822035;0.840120;,
  0.870060;0.216163;,
  0.866259;0.250660;,
  0.881516;0.236792;,
  0.674425;0.850972;,
  0.667666;0.884601;,
  0.813057;0.348231;,
  0.528411;0.897374;,
  0.540644;0.915383;,
  0.563341;0.923358;,
  0.587521;0.941394;,
  0.637498;0.954425;,
  0.064798;0.565847;,
  0.000000;0.700744;,
  0.196671;0.615539;,
  0.190200;0.886017;,
  0.097488;0.831138;,
  0.054302;0.859708;,
  0.173719;0.976776;,
  0.386291;0.813236;,
  0.348140;0.821776;,
  0.328485;1.000000;,
  0.456239;0.924285;,
  0.340234;0.492357;,
  0.181097;0.492619;,
  0.273727;0.628644;,
  0.524421;0.587946;,
  0.500751;0.641549;,
  0.562904;0.544541;,
  0.512287;0.715454;,
  0.513752;0.733362;,
  0.612666;0.000000;,
  0.500751;0.584374;,
  0.323491;0.711934;,
  0.500751;0.774887;,
  0.415258;0.768083;,
  0.305661;0.799419;;
 }
}
