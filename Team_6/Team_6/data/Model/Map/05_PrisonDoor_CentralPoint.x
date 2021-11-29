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
 146;
 51.06955;200.07150;-11.38580;,
 -48.92443;200.07150;-11.38580;,
 -48.92443;200.07150;1.57692;,
 51.06955;200.07150;1.57692;,
 51.06955;200.07150;1.57692;,
 -48.92443;200.07150;1.57692;,
 -48.92443;180.92386;1.57690;,
 51.06957;180.92386;1.57690;,
 51.06955;180.92386;-11.38580;,
 -48.92443;180.92386;-11.38580;,
 -48.92443;200.07150;-11.38580;,
 51.06955;200.07150;-11.38580;,
 -48.92443;180.92386;-11.38580;,
 -48.92443;180.92386;1.57690;,
 -48.92443;200.07150;1.57692;,
 -48.92443;200.07150;-11.38580;,
 51.06957;180.92386;1.57690;,
 51.06955;180.92386;-11.38580;,
 51.06955;200.07150;-11.38580;,
 51.06955;200.07150;1.57692;,
 25.19653;6.12332;-6.29182;,
 20.59963;6.12332;-6.29182;,
 20.59963;182.95535;-6.29182;,
 25.19653;182.95535;-6.29182;,
 22.89807;6.12332;-2.12968;,
 22.89807;182.95535;-2.12968;,
 25.19653;6.12332;-6.29182;,
 25.19653;182.95535;-6.29182;,
 20.59963;6.12332;-6.29182;,
 25.19653;6.12332;-6.29182;,
 22.89807;6.12332;-4.90444;,
 22.89807;6.12332;-2.12968;,
 25.19653;182.95535;-6.29182;,
 20.59963;182.95535;-6.29182;,
 22.89807;182.95535;-4.90444;,
 22.89807;182.95535;-2.12968;,
 5.84453;6.12332;-6.29182;,
 1.24766;6.12332;-6.29182;,
 1.24766;182.95535;-6.29182;,
 5.84453;182.95535;-6.29182;,
 3.54610;6.12332;-2.12968;,
 3.54610;182.95535;-2.12968;,
 5.84453;6.12332;-6.29182;,
 5.84453;182.95535;-6.29182;,
 1.24766;6.12332;-6.29182;,
 5.84453;6.12332;-6.29182;,
 3.54610;6.12332;-4.90444;,
 3.54610;6.12332;-2.12968;,
 5.84453;182.95535;-6.29182;,
 1.24766;182.95535;-6.29182;,
 3.54610;182.95535;-4.90444;,
 3.54610;182.95535;-2.12968;,
 -14.71211;6.12332;-6.29182;,
 -19.30901;6.12332;-6.29182;,
 -19.30901;182.95535;-6.29182;,
 -14.71211;182.95535;-6.29182;,
 -17.01056;6.12332;-2.12968;,
 -17.01056;182.95535;-2.12968;,
 -14.71211;6.12332;-6.29182;,
 -14.71211;182.95535;-6.29182;,
 -19.30901;6.12332;-6.29182;,
 -14.71211;6.12332;-6.29182;,
 -17.01056;6.12332;-4.90444;,
 -17.01056;6.12332;-2.12968;,
 -14.71211;182.95535;-6.29182;,
 -19.30901;182.95535;-6.29182;,
 -17.01056;182.95535;-4.90444;,
 -17.01056;182.95535;-2.12968;,
 41.68665;89.76414;-10.56768;,
 -44.52896;89.76414;-10.39326;,
 -44.52896;109.76414;-10.39326;,
 41.68665;109.76414;-10.56768;,
 -44.52896;109.76414;-1.89138;,
 41.68665;109.76414;-2.06580;,
 -44.52896;89.76414;-1.89138;,
 41.68665;89.76414;-2.06580;,
 -44.52896;89.76414;-10.39326;,
 41.68665;89.76414;-10.56768;,
 -44.52896;89.76414;-10.39326;,
 -44.52896;89.76414;-1.89138;,
 -44.52896;109.76414;-1.89138;,
 -44.52896;109.76414;-10.39326;,
 41.68665;89.76414;-2.06580;,
 41.68665;89.76414;-10.56768;,
 41.68665;109.76414;-10.56768;,
 41.68665;109.76414;-2.06580;,
 -30.08132;242.81593;-15.39462;,
 -30.08132;0.51256;-15.39462;,
 -49.94322;0.51256;-15.39462;,
 -49.94322;242.81593;-15.39462;,
 -30.08132;242.81593;10.20376;,
 -30.08132;242.81593;-15.39462;,
 -49.94322;242.81593;-15.39462;,
 -49.94322;242.81593;10.20376;,
 -30.08132;0.51256;10.20376;,
 -30.08132;242.81593;10.20376;,
 -49.94322;242.81593;10.20376;,
 -49.94322;0.51256;10.20376;,
 -30.08132;0.51256;-15.39462;,
 -30.08132;0.51256;10.20376;,
 -49.94322;0.51256;10.20376;,
 -49.94322;0.51256;-15.39462;,
 -49.94322;242.81593;-15.39462;,
 -49.94322;0.51256;-15.39462;,
 -49.94322;0.51256;10.20376;,
 -49.94322;242.81593;10.20376;,
 -30.08132;242.81593;-15.39462;,
 -30.08132;242.81593;10.20376;,
 -30.08132;0.51256;10.20376;,
 -30.08132;0.51256;-15.39462;,
 51.06955;0.51256;-11.38580;,
 -48.92443;0.51256;-11.38580;,
 -48.92443;9.36120;-11.38580;,
 51.06955;9.36120;-11.38580;,
 51.06955;0.51256;1.57692;,
 -48.92443;0.51256;1.57692;,
 -48.92443;0.51256;-11.38580;,
 51.06955;0.51256;-11.38580;,
 -48.92443;0.51256;-11.38580;,
 -48.92443;0.51256;1.57692;,
 -48.92443;9.36120;1.57692;,
 -48.92443;9.36120;-11.38580;,
 51.06955;0.51256;1.57692;,
 51.06955;0.51256;-11.38580;,
 51.06955;9.36120;-11.38580;,
 51.06955;9.36120;1.57692;,
 51.06955;9.36120;1.57692;,
 -48.92443;9.36120;1.57692;,
 -48.92443;0.51256;1.57692;,
 51.06955;0.51256;1.57692;,
 41.46097;6.12332;-8.27002;,
 37.06805;6.12332;-8.27002;,
 37.06805;182.95535;-8.27002;,
 41.46097;182.95535;-8.27002;,
 39.26453;6.12332;-5.50410;,
 39.26453;182.95535;-5.50410;,
 41.46097;6.12332;-8.27002;,
 41.46097;182.95535;-8.27002;,
 37.06805;6.12332;-8.27002;,
 41.46097;6.12332;-8.27002;,
 39.26453;6.12332;-7.34804;,
 39.26453;6.12332;-5.50410;,
 41.46097;182.95535;-8.27002;,
 37.06805;182.95535;-8.27002;,
 39.26453;182.95535;-7.34804;,
 39.26453;182.95535;-5.50410;;
 
 60;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;17,7,13,9;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 3;28,29,30;,
 3;31,28,30;,
 3;29,31,30;,
 3;32,33,34;,
 3;33,35,34;,
 3;35,32,34;,
 4;36,37,38,39;,
 4;37,40,41,38;,
 4;40,42,43,41;,
 3;44,45,46;,
 3;47,44,46;,
 3;45,47,46;,
 3;48,49,50;,
 3;49,51,50;,
 3;51,48,50;,
 4;52,53,54,55;,
 4;53,56,57,54;,
 4;56,58,59,57;,
 3;60,61,62;,
 3;63,60,62;,
 3;61,63,62;,
 3;64,65,66;,
 3;65,67,66;,
 3;67,64,66;,
 4;68,69,70,71;,
 4;71,70,72,73;,
 4;73,72,74,75;,
 4;75,74,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;113,121,127,125;,
 4;130,131,132,133;,
 4;131,134,135,132;,
 4;134,136,137,135;,
 3;138,139,140;,
 3;141,138,140;,
 3;139,141,140;,
 3;142,143,144;,
 3;143,145,144;,
 3;145,142,144;;
 
 MeshMaterialList {
  3;
  60;
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
  1,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.500000;0.500000;0.500000;;
   TextureFilename {
    "WallTexture2.png";
   }
  }
  Material {
   0.015686;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.081569;0.081569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  18;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000001;1.000000;,
  -0.875392;0.000000;0.483414;,
  0.000000;-1.000000;-0.000000;,
  -0.875392;0.000000;0.483413;,
  -0.875391;0.000000;0.483415;,
  -0.002023;0.000000;-0.999998;,
  0.002023;0.000000;0.999998;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.783109;0.000000;0.621885;,
  1.000000;0.000001;-0.000001;,
  0.875390;0.000000;0.483417;,
  0.875392;0.000000;0.483413;,
  0.875391;0.000000;0.483416;,
  0.783114;0.000000;0.621878;;
  60;
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;11,11,11,11;,
  4;13,13,13,13;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;14,14,14,14;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;15,15,15,15;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;1,1,1,1;,
  4;6,6,6,6;,
  4;16,16,16,16;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;7,7,7,7;,
  4;0,0,0,0;,
  4;8,8,8,8;,
  4;4,4,4,4;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;9,9,9,9;,
  4;4,4,4,4;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;9,9,9,9;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;12,12,12,12;,
  4;17,17,17,17;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;;
 }
 MeshTextureCoords {
  146;
  0.491424;0.110342;,
  0.491424;0.563951;,
  0.514519;0.563951;,
  0.514519;0.110342;,
  1.000000;-0.009675;,
  0.000000;-0.009675;,
  0.000000;0.065719;,
  1.000000;0.065719;,
  0.004620;0.072727;,
  1.000448;0.072727;,
  1.000448;-0.003928;,
  0.004620;-0.003928;,
  0.432107;0.064964;,
  0.567892;0.064964;,
  0.567892;-0.010131;,
  0.432107;-0.010131;,
  0.463503;0.064964;,
  0.536497;0.064964;,
  0.536497;-0.010131;,
  0.463503;-0.010131;,
  0.467505;0.045103;,
  0.467492;0.038343;,
  0.436993;0.038400;,
  0.437006;0.045160;,
  0.467480;0.031582;,
  0.436981;0.031639;,
  0.467467;0.024821;,
  0.436968;0.024879;,
  0.469196;0.041297;,
  0.491152;0.041256;,
  0.480669;0.034938;,
  0.480138;0.022262;,
  0.413421;0.041402;,
  0.435377;0.041360;,
  0.424894;0.035042;,
  0.424363;0.022367;,
  0.467505;0.045103;,
  0.467492;0.038343;,
  0.436993;0.038400;,
  0.437006;0.045160;,
  0.467480;0.031582;,
  0.436981;0.031639;,
  0.467467;0.024821;,
  0.436968;0.024879;,
  0.469196;0.041297;,
  0.491152;0.041256;,
  0.480669;0.034938;,
  0.480138;0.022262;,
  0.413421;0.041402;,
  0.435377;0.041360;,
  0.424894;0.035042;,
  0.424363;0.022367;,
  0.467505;0.045103;,
  0.467492;0.038343;,
  0.436993;0.038400;,
  0.437006;0.045160;,
  0.467480;0.031582;,
  0.436981;0.031639;,
  0.467467;0.024821;,
  0.436968;0.024879;,
  0.469196;0.041297;,
  0.491152;0.041256;,
  0.480669;0.034938;,
  0.480138;0.022262;,
  0.413421;0.041402;,
  0.435377;0.041360;,
  0.424894;0.035042;,
  0.424363;0.022367;,
  0.375000;0.061932;,
  0.625000;0.061932;,
  0.625000;-0.000952;,
  0.375000;-0.000952;,
  0.625000;0.058729;,
  0.375000;0.058729;,
  0.625000;0.002414;,
  0.375000;0.002414;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.167816;0.009379;,
  0.167816;0.062447;,
  0.220884;0.062447;,
  0.220884;0.009379;,
  0.687482;0.059520;,
  0.745319;0.059520;,
  0.745319;0.001683;,
  0.687482;0.001683;,
  0.740313;0.009376;,
  0.740313;1.026102;,
  0.850828;1.026102;,
  0.850828;0.009376;,
  0.514519;0.445457;,
  0.491424;0.445457;,
  0.491424;0.495797;,
  0.514519;0.495797;,
  0.261225;1.002534;,
  0.261225;0.002534;,
  0.150247;0.002534;,
  0.150247;1.002534;,
  0.589206;0.895178;,
  0.418701;0.895178;,
  0.418701;0.914100;,
  0.589206;0.914100;,
  0.001992;-0.002737;,
  0.001992;1.075935;,
  0.495787;1.075935;,
  0.495787;-0.002737;,
  0.998008;-0.002737;,
  0.504214;-0.002737;,
  0.504214;1.075935;,
  0.998008;1.075935;,
  0.004620;1.026102;,
  1.000448;1.026102;,
  1.000448;0.975833;,
  0.004620;0.975833;,
  0.418701;0.769213;,
  0.418701;0.939718;,
  0.589206;0.939718;,
  0.589206;0.769213;,
  0.432107;0.998008;,
  0.567892;0.998008;,
  0.567892;0.948763;,
  0.432107;0.948763;,
  0.463503;0.998008;,
  0.536497;0.998008;,
  0.536497;0.948763;,
  0.463503;0.948763;,
  1.000000;0.953092;,
  0.000000;0.953092;,
  0.000000;1.002534;,
  1.000000;1.002534;,
  0.467505;0.045103;,
  0.467492;0.038343;,
  0.436993;0.038400;,
  0.437006;0.045160;,
  0.467480;0.031582;,
  0.436981;0.031639;,
  0.467467;0.024821;,
  0.436968;0.024879;,
  0.469196;0.041297;,
  0.491152;0.041256;,
  0.480669;0.034938;,
  0.480138;0.022262;,
  0.413421;0.041402;,
  0.435377;0.041360;,
  0.424894;0.035042;,
  0.424363;0.022367;;
 }
}