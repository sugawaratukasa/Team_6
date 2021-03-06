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
 8.38905;-56.29185;-2.77945;,
 11.41710;-59.31995;5.09685;,
 15.31035;-47.64025;5.09685;,
 11.41710;-47.64025;-5.53615;,
 8.38905;-56.29185;12.97310;,
 11.41710;-47.64025;15.72980;,
 8.38905;-38.98865;12.97310;,
 11.41710;-35.96060;5.09685;,
 8.38905;-38.98865;-2.77945;,
 -0.26255;-32.06735;5.09685;,
 -0.26255;-35.96060;-5.53615;,
 -0.26255;-35.96060;15.72980;,
 -8.91420;-38.98865;12.97310;,
 -11.94225;-35.96060;5.09685;,
 -8.91420;-38.98865;-2.77945;,
 -15.83545;-47.64025;5.09685;,
 -11.94225;-47.64025;-5.53615;,
 -11.94225;-47.64025;15.72980;,
 -8.91420;-56.29185;12.97310;,
 -11.94225;-59.31995;5.09685;,
 -8.91420;-56.29185;-2.77945;,
 -0.26255;-63.21315;5.09685;,
 -0.26255;-59.31995;-5.53615;,
 -0.26255;-59.31995;15.72980;,
 8.38905;-56.29185;12.97310;,
 11.41710;-59.31995;5.09685;,
 8.38905;-56.29185;-2.77945;,
 -0.26255;-59.31995;15.72980;,
 -0.26255;-47.64025;19.27415;,
 -8.91420;-56.29185;12.97310;,
 -11.94225;-47.64025;15.72980;,
 -8.91420;-38.98865;12.97310;,
 -0.26255;-35.96060;15.72980;,
 -8.91420;-56.29185;-2.77945;,
 -0.26255;-59.31995;-5.53615;,
 -0.26255;-47.64025;-9.08045;,
 -11.94225;-47.64025;-5.53615;,
 -0.26255;-35.96060;-5.53615;,
 -8.91420;-38.98865;-2.77945;;
 
 24;
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;7,6,5,2;,
 4;8,7,2,3;,
 4;10,9,7,8;,
 4;9,11,6,7;,
 4;13,12,11,9;,
 4;14,13,9,10;,
 4;16,15,13,14;,
 4;15,17,12,13;,
 4;19,18,17,15;,
 4;20,19,15,16;,
 4;22,21,19,20;,
 4;21,23,18,19;,
 4;25,24,23,21;,
 4;26,25,21,22;,
 4;5,28,27,4;,
 4;28,30,29,27;,
 4;32,31,30,28;,
 4;6,32,28,5;,
 4;36,35,34,33;,
 4;35,3,0,34;,
 4;37,8,3,35;,
 4;38,37,35,36;;
 
 MeshMaterialList {
  2;
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
   0.800000;0.661961;0.561569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.500000;0.413725;0.350980;;
   TextureFilename {
    "nuno.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "nuno.jpg";
   }
  }
 }
 MeshNormals {
  26;
  0.562701;-0.562700;-0.605588;,
  0.562701;-0.562700;0.605588;,
  0.562700;0.562700;-0.605588;,
  0.562700;0.562700;0.605588;,
  -0.562700;0.562700;-0.605588;,
  -0.562700;0.562700;0.605588;,
  -0.562701;-0.562700;-0.605588;,
  -0.562700;-0.562700;0.605588;,
  0.000001;0.682741;-0.730660;,
  -0.682742;0.000000;0.730660;,
  -0.707107;-0.707106;0.000001;,
  -0.682741;0.000000;-0.730660;,
  0.000001;-0.682741;0.730660;,
  0.000001;-0.682741;-0.730661;,
  0.707107;-0.707107;0.000001;,
  0.682741;0.000000;0.730660;,
  0.707107;0.707107;0.000001;,
  0.682741;0.000000;-0.730661;,
  0.000001;0.682741;0.730660;,
  -0.707107;0.707106;0.000001;,
  1.000000;0.000000;0.000001;,
  0.000001;1.000000;0.000001;,
  -1.000000;0.000000;0.000001;,
  0.000001;-1.000000;0.000001;,
  0.000001;0.000000;1.000000;,
  0.000001;0.000000;-1.000000;;
  24;
  4;17,20,14,0;,
  4;20,15,1,14;,
  4;16,3,15,20;,
  4;2,16,20,17;,
  4;8,21,16,2;,
  4;21,18,3,16;,
  4;19,5,18,21;,
  4;4,19,21,8;,
  4;11,22,19,4;,
  4;22,9,5,19;,
  4;10,7,9,22;,
  4;6,10,22,11;,
  4;13,23,10,6;,
  4;23,12,7,10;,
  4;14,1,12,23;,
  4;0,14,23,13;,
  4;15,24,12,1;,
  4;24,9,7,12;,
  4;18,5,9,24;,
  4;3,18,24,15;,
  4;11,25,13,6;,
  4;25,17,0,13;,
  4;8,2,17,25;,
  4;4,8,25,11;;
 }
 MeshTextureCoords {
  39;
  0.514019;0.398368;,
  0.500000;0.398368;,
  0.500000;0.412387;,
  0.514019;0.412387;,
  0.485981;0.398368;,
  0.485981;0.412387;,
  0.485981;0.426405;,
  0.500000;0.426405;,
  0.514019;0.426405;,
  0.500000;0.440424;,
  0.514019;0.440424;,
  0.485981;0.440424;,
  0.485981;0.454442;,
  0.500000;0.454442;,
  0.514019;0.454442;,
  0.500000;0.468461;,
  0.514019;0.468461;,
  0.485981;0.468461;,
  0.485981;0.482479;,
  0.500000;0.482479;,
  0.514019;0.482479;,
  0.500000;0.496498;,
  0.514019;0.496498;,
  0.485981;0.496498;,
  0.485981;0.510516;,
  0.500000;0.510516;,
  0.514019;0.510516;,
  0.471963;0.398368;,
  0.471963;0.412387;,
  0.457944;0.398368;,
  0.457944;0.412387;,
  0.457944;0.426405;,
  0.471963;0.426405;,
  0.542056;0.398368;,
  0.528037;0.398368;,
  0.528037;0.412387;,
  0.542056;0.412387;,
  0.528037;0.426405;,
  0.542056;0.426405;;
 }
}
