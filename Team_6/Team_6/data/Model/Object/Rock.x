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
 39;
 541.73853;-388.64294;-375.48419;,
 -5.36267;-633.57288;-607.82764;,
 17.26637;-276.71121;-1007.09558;,
 620.24921;-7.96016;-607.82764;,
 -562.21851;-451.22186;-463.99481;,
 -855.89526;147.56451;-414.44528;,
 -5.36267;617.65210;-404.94885;,
 432.37677;463.69000;-428.99380;,
 -432.11389;537.81360;-303.17603;,
 -5.36267;1146.19946;17.78441;,
 620.24908;617.65210;17.78441;,
 -630.97437;617.65210;17.78441;,
 68.85148;820.66162;700.24658;,
 442.77292;513.99390;484.07513;,
 -417.37741;452.09027;643.39648;,
 -74.52338;-89.56055;1007.09558;,
 620.24921;-7.96016;643.39648;,
 -630.97437;-7.96016;643.39648;,
 355.73599;-560.56421;767.85382;,
 508.35834;-427.78729;651.96680;,
 -448.68646;-457.77856;539.57690;,
 262.81284;-870.00903;111.27591;,
 620.24921;-633.57288;17.78441;,
 -774.82098;-633.57288;17.78441;,
 -5.36267;-633.57288;-607.82764;,
 541.73853;-388.64294;-375.48419;,
 -562.21851;-451.22186;-463.99481;,
 -774.82098;-633.57288;17.78441;,
 -448.68646;-457.77856;539.57690;,
 -630.97437;-7.96016;643.39648;,
 -940.69641;18.18023;365.75812;,
 -417.37741;452.09027;643.39648;,
 -630.97437;617.65210;17.78441;,
 508.35834;-427.78729;651.96680;,
 620.24921;-633.57288;17.78441;,
 940.69641;-210.12888;131.85263;,
 620.24921;-7.96016;643.39648;,
 620.24908;617.65210;17.78441;,
 442.77292;513.99390;484.07513;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;7,6,9,10;,
 4;6,8,11,9;,
 4;10,9,12,13;,
 4;9,11,14,12;,
 4;13,12,15,16;,
 4;12,14,17,15;,
 4;16,15,18,19;,
 4;15,17,20,18;,
 4;19,18,21,22;,
 4;18,20,23,21;,
 4;22,21,24,25;,
 4;21,23,26,24;,
 4;27,28,29,30;,
 4;4,27,30,5;,
 4;30,29,31,32;,
 4;5,30,32,8;,
 4;33,34,35,36;,
 4;34,0,3,35;,
 4;36,35,37,38;,
 4;35,3,7,37;;
 
 MeshMaterialList {
  1;
  24;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Rock.jpg";
   }
  }
 }
 MeshNormals {
  35;
  0.607037;-0.603940;-0.516490;,
  0.276011;-0.820866;-0.499997;,
  -0.621792;-0.613261;-0.487120;,
  0.821175;-0.248600;-0.513682;,
  0.575875;-0.575913;-0.580252;,
  -0.747648;-0.390650;-0.537044;,
  0.535149;0.568088;-0.625213;,
  -0.022221;0.647066;-0.762110;,
  -0.509765;0.620246;-0.596183;,
  0.782332;0.619615;-0.063509;,
  -0.025249;0.749238;-0.661819;,
  -0.605768;0.642217;-0.469684;,
  0.696751;0.478880;0.534053;,
  0.608184;0.517233;0.602149;,
  -0.591449;0.502806;0.630376;,
  0.719059;0.064142;0.691982;,
  0.047433;0.014342;0.998771;,
  -0.615833;-0.060367;0.785561;,
  0.704352;-0.411723;0.578249;,
  0.658925;-0.400719;0.636587;,
  -0.452885;-0.634079;0.626769;,
  0.749055;-0.660126;-0.056127;,
  0.182080;-0.983042;-0.021784;,
  -0.628836;-0.765420;0.136742;,
  -0.973745;0.113568;0.197288;,
  0.999077;-0.040318;0.014819;,
  -0.520559;-0.476452;-0.708528;,
  0.249124;0.505382;-0.826151;,
  -0.018935;0.538169;-0.842624;,
  -0.550540;0.608392;-0.571633;,
  0.648279;0.692681;0.316112;,
  -0.588648;0.705360;0.394918;,
  -0.643264;0.586954;0.491626;,
  -0.541083;0.526283;0.655938;,
  -0.339291;-0.714426;0.611945;;
  24;
  4;0,1,4,3;,
  4;26,2,5,26;,
  4;27,28,7,6;,
  4;28,29,8,7;,
  4;6,7,10,9;,
  4;7,8,11,10;,
  4;9,30,13,12;,
  4;31,32,14,33;,
  4;12,13,16,15;,
  4;33,14,17,16;,
  4;15,16,19,18;,
  4;16,17,20,34;,
  4;18,19,22,21;,
  4;34,20,23,22;,
  4;21,22,1,0;,
  4;22,23,2,1;,
  4;23,20,17,24;,
  4;2,23,24,5;,
  4;24,17,14,32;,
  4;29,24,11,8;,
  4;18,21,25,15;,
  4;21,0,3,25;,
  4;15,25,9,12;,
  4;25,3,6,9;;
 }
 MeshTextureCoords {
  39;
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.375000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.500000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.500000;0.375000;,
  0.375000;0.375000;,
  0.625000;0.375000;,
  0.500000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.500000;0.625000;,
  0.375000;0.625000;,
  0.625000;0.625000;,
  0.500000;0.750000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.500000;0.875000;,
  0.375000;0.875000;,
  0.625000;0.875000;,
  0.500000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.750000;0.125000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.125000;0.250000;;
 }
}
