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
 85;
 10.58030;-11.64222;-3.17846;,
 0.00000;-15.57504;-1.75762;,
 0.00000;-22.43858;-7.61026;,
 16.03250;-17.09442;-7.61026;,
 -10.58030;-11.64222;-3.17846;,
 -16.03250;-17.09442;-7.61026;,
 -14.98190;-16.04382;-12.16876;,
 0.00000;-21.03778;-12.16876;,
 14.98190;-16.04382;-12.16876;,
 6.65756;-7.71948;-17.43286;,
 0.00000;-9.67800;-18.14058;,
 0.00000;-1.06192;-19.05052;,
 8.61608;-1.06192;-18.14058;,
 -6.65756;-7.71948;-17.43286;,
 -8.61608;-1.06192;-18.14058;,
 -6.65756;5.59564;-17.43286;,
 0.00000;7.55416;-18.14058;,
 6.65756;5.59564;-17.43286;,
 14.98190;13.91998;-12.16876;,
 0.00000;18.91394;-12.16876;,
 0.00000;20.31474;-7.61026;,
 16.03250;14.97058;-7.61026;,
 -14.98190;13.91998;-12.16876;,
 -16.03250;14.97058;-7.61026;,
 -10.58030;9.51838;-3.17846;,
 0.00000;13.45120;-1.75762;,
 10.58030;9.51838;-3.17846;,
 -0.00000;-1.06192;0.06916;,
 14.51312;-1.06192;-1.75762;,
 -14.51312;-1.06192;-1.75762;,
 -10.58030;-11.64222;-3.17846;,
 0.00000;-15.57504;-1.75762;,
 10.58030;-11.64222;-3.17846;,
 -14.51312;-1.06192;-1.75762;,
 -21.37666;-1.06192;-7.61026;,
 -10.58030;9.51838;-3.17846;,
 -16.03250;14.97058;-7.61026;,
 -14.98190;13.91998;-12.16876;,
 -19.97586;-1.06192;-12.16876;,
 10.58030;9.51838;-3.17846;,
 14.51312;-1.06192;-1.75762;,
 21.37666;-1.06192;-7.61026;,
 16.03250;14.97058;-7.61026;,
 19.97586;-1.06192;-12.16876;,
 14.98190;13.91998;-12.16876;,
 14.98190;-16.04382;-12.16876;,
 0.00000;-21.03778;-12.16876;,
 0.00000;-17.07266;-12.69208;,
 12.00806;-13.06998;-12.69208;,
 -14.98190;-16.04382;-12.16876;,
 -12.00806;-13.06998;-12.69208;,
 -10.85764;-11.91956;-12.68098;,
 0.00000;-15.53878;-12.68098;,
 10.85764;-11.91956;-12.68098;,
 -19.97586;-1.06192;-12.16876;,
 -16.01074;-1.06192;-12.69208;,
 -14.98190;13.91998;-12.16876;,
 -12.00806;10.94614;-12.69208;,
 -10.85764;9.79572;-12.68098;,
 -14.47686;-1.06192;-12.68098;,
 0.00000;18.91394;-12.16876;,
 0.00000;14.94882;-12.69208;,
 14.98190;13.91998;-12.16876;,
 12.00806;10.94614;-12.69208;,
 10.85764;9.79572;-12.68098;,
 0.00000;13.41494;-12.68098;,
 19.97586;-1.06192;-12.16876;,
 16.01074;-1.06192;-12.69208;,
 14.47686;-1.06192;-12.68098;,
 10.85764;-11.91956;-12.68098;,
 0.00000;-15.53878;-12.68098;,
 0.00000;-13.78876;-15.41078;,
 9.54512;-10.60704;-15.41078;,
 -10.85764;-11.91956;-12.68098;,
 -9.54512;-10.60704;-15.41078;,
 -14.47686;-1.06192;-12.68098;,
 -12.72684;-1.06192;-15.41078;,
 -10.85764;9.79572;-12.68098;,
 -9.54512;8.48322;-15.41078;,
 0.00000;13.41494;-12.68098;,
 0.00000;11.66492;-15.41078;,
 10.85764;9.79572;-12.68098;,
 9.54512;8.48322;-15.41078;,
 14.47686;-1.06192;-12.68098;,
 12.72684;-1.06192;-15.41078;;
 
 56;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;2,5,6,7;,
 4;3,2,7,8;,
 4;9,10,11,12;,
 4;10,13,14,11;,
 4;11,14,15,16;,
 4;12,11,16,17;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;20,23,24,25;,
 4;21,20,25,26;,
 4;26,25,27,28;,
 4;25,24,29,27;,
 4;27,29,30,31;,
 4;28,27,31,32;,
 4;4,33,34,5;,
 4;33,35,36,34;,
 4;34,36,37,38;,
 4;5,34,38,6;,
 4;39,40,41,42;,
 4;40,0,3,41;,
 4;41,3,8,43;,
 4;42,41,43,44;,
 4;45,46,47,48;,
 4;46,49,50,47;,
 4;47,50,51,52;,
 4;48,47,52,53;,
 4;49,54,55,50;,
 4;54,56,57,55;,
 4;55,57,58,59;,
 4;50,55,59,51;,
 4;56,60,61,57;,
 4;60,62,63,61;,
 4;61,63,64,65;,
 4;57,61,65,58;,
 4;62,66,67,63;,
 4;66,45,48,67;,
 4;67,48,53,68;,
 4;63,67,68,64;,
 4;69,70,71,72;,
 4;70,73,74,71;,
 4;71,74,13,10;,
 4;72,71,10,9;,
 4;73,75,76,74;,
 4;75,77,78,76;,
 4;76,78,15,14;,
 4;74,76,14,13;,
 4;77,79,80,78;,
 4;79,81,82,80;,
 4;80,82,17,16;,
 4;78,80,16,15;,
 4;81,83,84,82;,
 4;83,69,72,84;,
 4;84,72,9,12;,
 4;82,84,12,17;;
 
 MeshMaterialList {
  5;
  56;
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  2,
  2,
  0,
  0,
  2,
  2,
  0,
  0,
  2,
  2,
  0,
  0,
  2,
  2,
  3,
  3,
  1,
  1,
  3,
  3,
  1,
  1,
  3,
  3,
  1,
  1,
  3,
  3,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.500000;0.500000;0.500000;;
   TextureFilename {
    "Hazard_texture.jpg";
   }
  }
  Material {
   0.800000;0.031373;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.600000;0.023529;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.630588;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.472941;0.000000;0.000000;;
  }
  Material {
   0.800000;0.062745;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.600000;0.047059;0.000000;;
  }
 }
 MeshNormals {
  66;
  0.334173;-0.334173;0.881282;,
  -0.334173;-0.334173;0.881282;,
  0.672298;-0.672298;-0.309890;,
  -0.672298;-0.672298;-0.309890;,
  0.672298;0.672298;-0.309890;,
  -0.672298;0.672298;-0.309890;,
  0.334173;0.334173;0.881282;,
  -0.334173;0.334173;0.881282;,
  0.315418;-0.315418;-0.894999;,
  -0.315418;-0.315418;-0.894999;,
  -0.315419;0.315419;-0.894998;,
  0.315419;0.315419;-0.894998;,
  0.280856;-0.280856;-0.917736;,
  -0.280856;-0.280856;-0.917736;,
  -0.280855;0.280855;-0.917736;,
  0.280855;0.280855;-0.917736;,
  -0.955886;-0.000000;-0.293738;,
  0.955886;-0.000000;-0.293738;,
  -0.041289;-0.041289;-0.998294;,
  0.000000;-0.467351;-0.884072;,
  0.041289;-0.041289;-0.998294;,
  -0.041289;0.041289;-0.998294;,
  -0.467351;-0.000000;-0.884072;,
  0.041289;0.041289;-0.998294;,
  0.000000;0.467352;-0.884071;,
  0.467351;-0.000000;-0.884072;,
  -0.479545;-0.479545;-0.734897;,
  0.479545;-0.479545;-0.734897;,
  -0.479545;0.479545;-0.734897;,
  0.479545;0.479545;-0.734897;,
  0.000000;-0.376689;0.926340;,
  -0.418731;-0.418730;0.805810;,
  0.000000;-0.955886;-0.293738;,
  0.418731;-0.418730;0.805810;,
  0.000000;-0.320540;-0.947235;,
  -0.320540;-0.000000;-0.947235;,
  0.000000;0.320540;-0.947235;,
  0.320540;-0.000000;-0.947235;,
  0.000000;0.955886;-0.293738;,
  0.000000;0.376689;0.926340;,
  -0.376689;-0.000000;0.926340;,
  0.376689;-0.000000;0.926340;,
  0.000000;-0.585216;0.810878;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.585216;-0.000000;0.810878;,
  0.585216;-0.000000;0.810878;,
  0.000000;-0.061921;-0.998081;,
  -0.061921;-0.000000;-0.998081;,
  0.000000;0.061921;-0.998081;,
  0.061921;-0.000000;-0.998081;,
  0.000000;-0.692873;-0.721060;,
  -0.692873;-0.000000;-0.721060;,
  0.000000;0.692873;-0.721060;,
  0.692873;-0.000000;-0.721060;,
  0.000000;0.585216;0.810878;,
  -0.418731;0.418730;0.805810;,
  0.418731;0.418730;0.805810;,
  0.087314;-0.087314;-0.992347;,
  0.000000;-0.130846;-0.991403;,
  -0.087314;-0.087314;-0.992347;,
  -0.130846;-0.000000;-0.991403;,
  -0.087314;0.087314;-0.992347;,
  0.000000;0.130846;-0.991403;,
  0.087314;0.087314;-0.992347;,
  0.130846;-0.000000;-0.991403;;
  56;
  4;0,30,42,33;,
  4;30,1,31,42;,
  4;32,3,3,32;,
  4;2,32,32,2;,
  4;12,34,43,37;,
  4;34,13,35,43;,
  4;43,35,14,36;,
  4;37,43,36,15;,
  4;4,38,38,4;,
  4;38,5,5,38;,
  4;55,56,7,39;,
  4;57,55,39,6;,
  4;6,39,44,41;,
  4;39,7,40,44;,
  4;44,40,1,30;,
  4;41,44,30,0;,
  4;1,40,45,31;,
  4;40,7,56,45;,
  4;16,5,5,16;,
  4;3,16,16,3;,
  4;6,41,46,57;,
  4;41,0,33,46;,
  4;17,2,2,17;,
  4;4,17,17,4;,
  4;58,59,47,20;,
  4;59,60,18,47;,
  4;47,18,9,19;,
  4;20,47,19,8;,
  4;60,61,48,18;,
  4;61,62,21,48;,
  4;48,21,10,22;,
  4;18,48,22,9;,
  4;62,63,49,21;,
  4;63,64,23,49;,
  4;49,23,11,24;,
  4;21,49,24,10;,
  4;64,65,50,23;,
  4;65,58,20,50;,
  4;50,20,8,25;,
  4;23,50,25,11;,
  4;8,19,51,27;,
  4;19,9,26,51;,
  4;51,26,13,34;,
  4;27,51,34,12;,
  4;9,22,52,26;,
  4;22,10,28,52;,
  4;52,28,14,35;,
  4;26,52,35,13;,
  4;10,24,53,28;,
  4;24,11,29,53;,
  4;53,29,15,36;,
  4;28,53,36,14;,
  4;11,25,54,29;,
  4;25,8,27,54;,
  4;54,27,12,37;,
  4;29,54,37,15;;
 }
 MeshTextureCoords {
  85;
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.875000;,
  0.375000;0.875000;,
  0.625000;1.000000;,
  0.625000;0.875000;,
  0.625000;0.750000;,
  0.500000;0.750000;,
  0.375000;0.750000;,
  0.430556;0.694444;,
  0.500000;0.718750;,
  0.500000;0.625000;,
  0.406250;0.625000;,
  0.569444;0.694444;,
  0.593750;0.625000;,
  0.569444;0.555556;,
  0.500000;0.531250;,
  0.430556;0.555556;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.375000;,
  0.375000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.375000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.125000;,
  0.375000;0.125000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.500000;0.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.875000;,
  0.875000;1.000000;,
  0.875000;0.875000;,
  0.875000;0.750000;,
  0.750000;0.750000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.875000;,
  0.125000;0.875000;,
  0.250000;0.750000;,
  0.125000;0.750000;,
  0.329243;0.670757;,
  0.500000;0.670757;,
  0.500000;0.656794;,
  0.382405;0.617595;,
  0.670757;0.670757;,
  0.617595;0.617595;,
  0.642831;0.642831;,
  0.500000;0.642831;,
  0.357169;0.642831;,
  0.670757;0.500000;,
  0.656794;0.500000;,
  0.670757;0.329243;,
  0.617595;0.382405;,
  0.642831;0.357169;,
  0.642831;0.500000;,
  0.500000;0.329243;,
  0.500000;0.343206;,
  0.329243;0.329243;,
  0.382405;0.382405;,
  0.357169;0.357169;,
  0.500000;0.357169;,
  0.329243;0.500000;,
  0.343206;0.500000;,
  0.357169;0.500000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.500000;0.750000;,
  0.406250;0.718750;,
  0.625000;0.750000;,
  0.593750;0.718750;,
  0.625000;0.625000;,
  0.625000;0.625000;,
  0.625000;0.500000;,
  0.593750;0.531250;,
  0.500000;0.500000;,
  0.500000;0.500000;,
  0.375000;0.500000;,
  0.406250;0.531250;,
  0.375000;0.625000;,
  0.375000;0.625000;;
 }
}