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
 48;
 -44.67332;152.26605;20.22550;,
 -88.58433;152.26605;20.22550;,
 -88.58433;152.26605;-18.06202;,
 -44.67332;152.26605;-18.06202;,
 -44.67328;0.94337;-18.06202;,
 -45.77092;-0.12983;-17.10494;,
 -45.77092;-0.12983;19.26842;,
 -44.67328;0.94337;20.22550;,
 -88.58427;0.94337;-18.06202;,
 -87.48664;-0.12983;-17.10494;,
 -88.58427;0.94337;20.22550;,
 -87.48664;-0.12983;19.26842;,
 0.22969;152.26605;20.22550;,
 -43.68130;152.26605;20.22550;,
 -43.68130;152.26605;-18.06202;,
 0.22969;152.26605;-18.06202;,
 0.22972;0.94336;-18.06202;,
 -0.86790;-0.12984;-17.10494;,
 -0.86790;-0.12984;19.26842;,
 0.22972;0.94336;20.22550;,
 -43.68126;0.94337;-18.06202;,
 -42.58362;-0.12984;-17.10494;,
 -43.68126;0.94337;20.22550;,
 -42.58362;-0.12984;19.26842;,
 45.01517;152.26605;20.22550;,
 1.10419;152.26605;20.22550;,
 1.10419;152.26605;-18.06202;,
 45.01517;152.26605;-18.06202;,
 45.01522;0.94335;-18.06202;,
 43.91758;-0.12984;-17.10494;,
 43.91758;-0.12984;19.26842;,
 45.01522;0.94335;20.22550;,
 1.10422;0.94336;-18.06202;,
 2.20186;-0.12984;-17.10494;,
 1.10422;0.94336;20.22550;,
 2.20186;-0.12984;19.26842;,
 89.73599;152.26605;20.22550;,
 45.82501;152.26605;20.22550;,
 45.82501;152.26605;-18.06202;,
 89.73599;152.26605;-18.06202;,
 89.73602;0.94335;-18.06202;,
 88.63840;-0.12984;-17.10494;,
 88.63840;-0.12984;19.26842;,
 89.73602;0.94335;20.22550;,
 45.82504;0.94335;-18.06202;,
 46.92270;-0.12984;-17.10494;,
 45.82504;0.94335;20.22550;,
 46.92270;-0.12984;19.26842;;
 
 40;
 4;3,2,1,0;,
 4;7,6,5,4;,
 4;9,8,4,5;,
 4;11,10,8,9;,
 4;10,11,6,7;,
 4;4,8,2,3;,
 4;6,11,9,5;,
 4;0,1,10,7;,
 4;8,10,1,2;,
 4;7,4,3,0;,
 4;15,14,13,12;,
 4;19,18,17,16;,
 4;21,20,16,17;,
 4;23,22,20,21;,
 4;22,23,18,19;,
 4;16,20,14,15;,
 4;18,23,21,17;,
 4;12,13,22,19;,
 4;20,22,13,14;,
 4;19,16,15,12;,
 4;27,26,25,24;,
 4;31,30,29,28;,
 4;33,32,28,29;,
 4;35,34,32,33;,
 4;34,35,30,31;,
 4;28,32,26,27;,
 4;30,35,33,29;,
 4;24,25,34,31;,
 4;32,34,25,26;,
 4;31,28,27,24;,
 4;39,38,37,36;,
 4;43,42,41,40;,
 4;45,44,40,41;,
 4;47,46,44,45;,
 4;46,47,42,43;,
 4;40,44,38,39;,
 4;42,47,45,41;,
 4;36,37,46,43;,
 4;44,46,37,38;,
 4;43,40,39,36;;
 
 MeshMaterialList {
  4;
  40;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.300000;0.300000;0.300000;;
   TextureFilename {
    "22oeo24p-900.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.300000;0.300000;0.300000;;
   TextureFilename {
    "22oeo24p-900.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.300000;0.300000;0.300000;;
   TextureFilename {
    "22oeo24p-900.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.300000;0.300000;0.300000;;
   TextureFilename {
    "22oeo24p-900.jpg";
   }
  }
 }
}
