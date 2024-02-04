#pragma once

class xPlane
{
public:
    float   fa, fb, fc, fd;
    void	Normalize()
    {
        float fMag = sqrt(fa * fa + fb * fb + fc * fc);
        fa = fa / fMag;
        fb = fb / fMag;
        fc = fc / fMag;
        fd = fd / fMag;
    }
    void   CreatePlane(Vec3 v0, Vec3 v1, Vec3 v2)
    {
        Vec3 vE0 = v1 - v0;
        Vec3 vE1 = v2 - v0;
        Vec3 vNormal =vE1;
        vE0.Cross(vE1 , vNormal);
        vNormal.Normalize();
        fa = vNormal.x;
        fb = vNormal.y;
        fc = vNormal.z;
        fd = -(fa * v0.x + fb * v0.y + fc * v0.z);
    }
    void   CreatePlane(Vec3 v0, Vec3 vNormal)
    {
        vNormal.Normalize();
        fa = vNormal.x;
        fb = vNormal.y;
        fc = vNormal.z;
        fd = -(fa * v0.x + fb * v0.y + fc * v0.z);
    }
};
class FrustumBox
{
public:
    Vec3  frustum[8];
    xPlane    xPlane[6];
    void      Create(Matrix matView, Matrix matProj)
    {
        Matrix mat = matView * matProj;
        mat=mat.Invert();
        // 5   6
        // 4   7
        // 
        // 1   2
        // 0   3
        frustum[0] = Vec3(-1.0f, -1.0f, 0.0f);
        frustum[1] = Vec3(-1.0f, 1.0f, 0.0f);
        frustum[2] = Vec3(1.0f, 1.0f, 0.0f);
        frustum[3] = Vec3(1.0f, -1.0f, 0.0f);

        frustum[4] = Vec3(-1.0f, -1.0f, 1.0f);
        frustum[5] = Vec3(-1.0f, 1.0f, 1.0f);
        frustum[6] = Vec3(1.0f, 1.0f, 1.0f);
        frustum[7] = Vec3(1.0f, -1.0f, 1.0f);

        for (int i = 0; i < 8; i++)
        {
            frustum[i].Transform(frustum[i], mat, frustum[i]);
        }

        xPlane[0].CreatePlane(frustum[5], frustum[0], frustum[1]);	// 좌 평면(left)
        xPlane[1].CreatePlane(frustum[3], frustum[6], frustum[2]);	// 우 평면(right)
        xPlane[2].CreatePlane(frustum[5], frustum[2], frustum[6]);	// 상 평면(top)
        xPlane[3].CreatePlane(frustum[0], frustum[7], frustum[3]);	// 하 평면(bottom)
        xPlane[4].CreatePlane(frustum[0], frustum[2], frustum[1]);	// 근 평면(near)
        xPlane[5].CreatePlane(frustum[6], frustum[4], frustum[5]);	// 원 평면(far)
    }
    BOOL      CheckOBBInPlane(Terrain_Cube& box)
    {
        int count = 0;
        float distance = 0.0f;
        float planeToCenter = 0.0f;
        Vec3 dirVector;
        for (int iplane = 0; iplane < 6; iplane++)
        {
            dirVector = box.axis[0] * box.extent[0];
            distance = fabs(xPlane[iplane].fa * dirVector.x +
                xPlane[iplane].fb * dirVector.y +
                xPlane[iplane].fc * dirVector.z);
            dirVector = box.axis[1] * box.extent[1];
            distance += fabs(xPlane[iplane].fa * dirVector.x +
                xPlane[iplane].fb * dirVector.y +
                xPlane[iplane].fc * dirVector.z);
            dirVector = box.axis[2] * box.extent[2];
            distance += fabs(xPlane[iplane].fa * dirVector.x +
                xPlane[iplane].fb * dirVector.y +
                xPlane[iplane].fc * dirVector.z);

            planeToCenter = xPlane[iplane].fa * box.center.x +
                xPlane[iplane].fb * box.center.y +
                xPlane[iplane].fc * box.center.z +
                xPlane[iplane].fd;
            if (planeToCenter <= -distance)
            {
                return false;
            }
        }
        return TRUE;
    }

};


class FrustomCamera : public MonoBehaviour
{
public:
    shared_ptr<FrustumBox> frustomBox;
public:
    FrustomCamera() {
        frustomBox = make_shared<FrustumBox>();
    };
    ~FrustomCamera() {};
public:
	virtual void Update() override;
};

