#ifndef LIN_H
#define LIN_H

class Lin
{
private:
  double x,y,z;
  double norm;
public:
  Lin ();
  Lin (double x0, double y0, double z0);
  Lin& operator= (const Lin& c);
  ~Lin () {}
  double X () const;
  double Y () const;
  double Z () const;
  double abs () const;
  Lin unit ();
  friend Lin operator+ (const Lin&  a, const Lin& b);
  friend Lin operator- (const Lin&  a, const Lin& b);
  friend Lin operator* (const double&  a, const Lin& b);
  friend Lin operator/ (const Lin&  r, const Lin& v);
  void read () const;
};

inline Lin operator+ (const Lin& a, const Lin& b)
{ return Lin (a.X()+b.X(), a.Y()+b.Y(), a.Z()+b.Z()); }

inline Lin operator- (const Lin& a, const Lin& b)
{ return Lin (a.X()-b.X(), a.Y()-b.Y(), a.Z()-b.Z()); }

inline Lin operator* (const double& a, const Lin& b)
{ return Lin (a*b.X(), a*b.Y(), a*b.Z()); }

inline Lin operator*= (const Lin& r, const Lin& v)
{ return Lin(r.Y()*v.Z()-r.Z()*v.Y(),-r.X()*v.Z()+r.Z()*v.X(),r.X()*v.Y()-r.Y()*v.X()); }

#endif
