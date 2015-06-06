bool bbb;
String s;

void f() {
}

void main() {
  int aaa;
  float ccc;

  aaa = f + f;
  ccc = f + f;
  bbb = f && f;
  bbb = f == f;
  bbb = f > f;

  // Binary arithmetic operators ---------------------------
  aaa = aaa + 1.0;
  aaa = aaa + true;
  aaa = aaa + "foo";
  aaa = aaa + s;
  aaa = s + aaa;
  aaa = s + s;

  // Binary Boolean operators ---------------------------
  bbb = bbb && 1.0;
  bbb = bbb && true;
  bbb = bbb && "foo";
  bbb = bbb && s;
  bbb = s && bbb;
  bbb = s && s;

  // Binary relational operators ---------------------------
  bbb = aaa == 1;
  bbb = aaa != 1;
  bbb = aaa > 1;
  bbb = aaa < 1;
  bbb = aaa == 1.0;
  bbb = aaa != 1.0;
  bbb = aaa > 1.0;
  bbb = aaa < 1.0;
  bbb = aaa == true;
  bbb = aaa != true;
  bbb = aaa > true;
  bbb = aaa < true;

  // Test the prevention of cascades of error messages ---------
  bbb = (aaa + 1.0) && (bbb < true);

  return;
}
