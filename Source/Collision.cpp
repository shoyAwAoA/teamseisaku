#include"Collision.h"

//���Ƌ��̌�������
bool Collision::IntersectSphereVeSphere(
    const DirectX::XMFLOAT3& positionA,
    float radiusA,
    const DirectX::XMFLOAT3& positionB,
    float radiusB,
    DirectX::XMFLOAT3& outPositionB)
{
    //A->B�̒P�ʃx�N�g�����Z�o
    DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
    DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
    DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB,PositionA);
    DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
        float lengthSq;
    DirectX::XMStoreFloat(&lengthSq, LengthSq);

    //��������
    float range = radiusA + radiusB ;
    if (range < lengthSq)
    {
    return false;
        
    }
    //A��B�������o��
    Vec = DirectX::XMVector3Normalize(Vec);
   //��L�̃x�N�g����range���X�P�[��
    Vec =DirectX::XMVectorScale(Vec,range);
    //���̃x�N�g�����ʒuA(PositionA)����̑������ʒu�Ɉړ�
    Vec =DirectX::XMVectorAdd(PositionA,Vec);
    //�o�͗p�̈ʒu�ioutPositionB)�ɑ������
    DirectX::XMStoreFloat3(&outPositionB, Vec);
        return true; 
}
//�~���Ɖ~���̌�������
bool Collision::IntersectCylinderVsCylinder(
    const DirectX::XMFLOAT3& positionA,
    float radiusA,
    float heightA,
    const DirectX::XMFLOAT3& positionB,
    float radiusB,
    float heightB,
    DirectX::XMFLOAT3& outPositionB)
{
    //A�̑�����B�̓�����Ȃ瓖�����Ă��Ȃ�
    if (positionA.y > positionB.y+heightB)//y���W�͑���
    {
        return false;
    }
    //A�̓���B�̑�����艺�Ȃ瓖�����Ă��Ȃ�
    if (positionA.y + heightA < positionB.y)
    {
        return false;
    }
    //XZ���ʂł͈̔̓`�F�b�N
    float vx = positionB.x - positionA.x;
    float vz = positionB.z - positionA.z;
    float range = radiusA + radiusB;
    float distXZ = sqrtf(vx * vx + vz * vz);//A��B�̋���
    
    if (distXZ > range)
    {
        return false;
    }
    if (distXZ <= 0.0f)
    {
        outPositionB.x = positionB.x;
        outPositionB.y = positionB.y;
        outPositionB.z = positionB.z;
        return true;
    }
    //A��B�������o��
    vx /= distXZ;
    vz /= distXZ;
   /* distXZ /= vx    
            
   ;
    distXZ /= vz;*/
    
   /* outPositionB.x = positionB.x + (vx * range);
    outPositionB.y = positionB.y;
    outPositionB.z = positionB.z + (vz * range);
    */
    outPositionB.x = positionA.x + ( vx*range);
    outPositionB.y = positionB.y;
    outPositionB.z = positionA.z + ( vz*range);
   /* outPositionB.x = positionB.x + ( vx*range);
    outPositionB.y = positionB.y;
    outPositionB.z = positionB.z + ( vz*range);*/

    return true;
}

bool Collision::IntersectSphereVsCylinder(
    const DirectX::XMFLOAT3& spherePosition,
    float sphereRadius, 
    const DirectX::XMFLOAT3& cylinderPosition, 
    float cylinderRadius,
    float cylinderHeight,
    DirectX::XMFLOAT3& outCylinderPosition)
{
    if (spherePosition.y + sphereRadius < cylinderPosition.y) { return false; }
    if (spherePosition.y - sphereRadius > (cylinderPosition.y + cylinderHeight)) { return false; }

    float vx=cylinderPosition.x-spherePosition.x;
    float vz = cylinderPosition.z - spherePosition.z;
    float range = (sphereRadius + cylinderRadius);
    float distXZ = sqrtf(vx * vx + vz * vz);//A��B�̋���

    if (distXZ > range)//�ڂ��Ă��Ȃ�
    {
        return false;
    }
    vx /= distXZ;
    vz /= distXZ;

    outCylinderPosition.x = spherePosition.x + (vx * range);
    outCylinderPosition.y = spherePosition.y;
    outCylinderPosition.z = spherePosition.z + (vz * range);

    return true;
}

//���C�ƃ��f���̌�������
bool Collision::IntersectRayVsModel(
    const DirectX::XMFLOAT3& start,
    const DirectX::XMFLOAT3& end,
    const Model* model, 
    HitResult& result)
{
    //DirectX::XMVECTOR WorldStart = DirectX::XMLoadFloat3(&start);
    //DirectX::XMVECTOR WorldEnd = DirectX::XMLoadFloat3(&end);
    //DirectX::XMVECTOR WorldRayVec = DirectX::XMVectorSubtract(WorldEnd, WorldStart);
    //DirectX::XMVECTOR WorldRayLength = DirectX::XMVector3Length(WorldRayVec);


    ////���[���h��Ԃ̃��C�̒���
    //DirectX::XMStoreFloat(&result.distance, WorldRayLength);

    //bool hit = false;

    //const ModelResource* resource = model->GetResource();
    //for (const ModelResource::Mesh& mesh : resource->GetMeshes())
    //{
    //    //���b�V���m�[�h�擾
    //    const Model::Node& node = model->GetNodes().at(mesh.nodeIndex);

    //    //���C�����[���h��Ԃ��烍�[�J����Ԃ֕ϊ�
    //    DirectX::XMMATRIX WorldTransform = DirectX::XMLoadFloat4x4(&node.worldTransform);
    //    DirectX::XMMATRIX InverseWorldTransform = DirectX::XMMatrixInverse(nullptr, WorldTransform);

    //    DirectX::XMVECTOR S = DirectX::XMVector3TransformCoord(WorldStart, InverseWorldTransform);
    //    DirectX::XMVECTOR E = DirectX::XMVector3TransformCoord(WorldEnd, InverseWorldTransform);
    //    DirectX::XMVECTOR SE = DirectX::XMVectorSubtract(E, S);
    //    DirectX::XMVECTOR V = DirectX::XMVector3Normalize(SE);
    //    DirectX::XMVECTOR Length = DirectX::XMVector3Length(SE);

    //    //���C�̒���
    //    float neart;
    //    DirectX::XMStoreFloat(&neart, Length);

    //    //�O�p�`�i�ʁj�Ƃ̌�������
    //    const std::vector<ModelResource::Vertex>& vertices = mesh.vertices;
    //    const std::vector<UINT>indices = mesh.indices;

    //    int materialIndex = -1;
    //    DirectX::XMVECTOR HitPosition;
    //    DirectX::XMVECTOR HitNormal;
    //    for (const ModelResource::Subset& subset : mesh.subsets)
    //    {
    //        for (UINT i = 0; i < subset.indexCount; i += 3)
    //        {
    //            UINT index = subset.startIndex + i;
    //            //�O�p�`�̒��_�𒊏o
    //            const ModelResource::Vertex& a = vertices.at(indices.at(index));
    //            const ModelResource::Vertex& b = vertices.at(indices.at(index + 1));
    //            const ModelResource::Vertex& c = vertices.at(indices.at(index + 2));

    //            DirectX::XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
    //            DirectX::XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
    //            DirectX::XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

    //            //�O�p�`�̎O�Ӄx�N�g�����Z�o
    //            DirectX::XMVECTOR AB = DirectX::XMVectorSubtract(B, A);//�I�_-�n�_�Ńx�N�g�����Z�o����
    //            DirectX::XMVECTOR BC = DirectX::XMVectorSubtract(C, B);
    //            DirectX::XMVECTOR CA = DirectX::XMVectorSubtract(A, C);

    //            //�O�p�`�̖@���x�N�g�����Z�o
    //            DirectX::XMVECTOR N = DirectX::XMVector3Cross(AB, BC);//�@���x�N�g���͓�̃x�N�g�����g���O�ς��v�Z���ċ��߂�

    //            //���ς̌��ʂ��v���X�Ȃ痠����
    //            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(V,N);
    //            float d;//�t���[�g�^�����
    //            DirectX::XMStoreFloat(&d, Dot);//�x�N�^�[�^����t���[�g�^�ɂ���

    //            if (d>=0)continue;

    //            //���C�ƕ��ʂ̌�_���Z�o
    //            DirectX::XMVECTOR SA = DirectX::XMVectorSubtract(A, S);
    //            DirectX::XMVECTOR X = DirectX::XMVectorDivide(DirectX::XMVector3Dot(N,SA),Dot);
    //                //DirectX::XMVectorDivide��
    //                //2��XMVECTOR�C���X�^���X�̂���
    //                //���������Ŋ���A
    //                //���ʂ�V����XMVECTOR�C���X�^���X�Ɋi�[����֐�
    //                //XMVector�RDot�̈�߂̃x�N�^�[�̂Ȃ��ɖ@���x�N�g����
    //                //��ڂ̃x�N�^�[�ɂ�SA������
    //                //DirectX::XMVectorDivide()�̉E���͓��ς̌��ʂ�����
    //            float x;
    //            DirectX::XMStoreFloat(&x, X);
    //            if (x<.0f || x>neart)continue;//��_�܂ł̋��������܂łɌv�Z�����ŋߋ������傫���Ƃ��̓X�L�b�v

    //            DirectX::XMVECTOR P = DirectX::XMVectorAdd( DirectX::XMVectorMultiply(V, X),S);

    //            //��_���O�p�`�̓����ɂ��邩����
    //            //���
    //            DirectX::XMVECTOR PA = DirectX::XMVectorSubtract(A, P);
    //            DirectX::XMVECTOR Cross1 = DirectX::XMVector3Cross(PA, AB);
    //            DirectX::XMVECTOR Dot1 = DirectX::XMVector3Dot(Cross1, N);
    //            float dot1;
    //            DirectX::XMStoreFloat(&dot1, Dot1);
    //            if (dot1 < 0.0f)continue;

    //            //���
    //            DirectX::XMVECTOR PB = DirectX::XMVectorSubtract(B, P);
    //            DirectX::XMVECTOR Cross2 = DirectX::XMVector3Cross(PB, BC);
    //            DirectX::XMVECTOR Dot2 = DirectX::XMVector3Dot(Cross2, N);
    //            float dot2;
    //            DirectX::XMStoreFloat(&dot2, Dot2);
    //            if (dot2 < 0.0f)continue;

    //            //�O��
    //            DirectX::XMVECTOR PC = DirectX::XMVectorSubtract(C, P);
    //            DirectX::XMVECTOR Cross3 = DirectX::XMVector3Cross(PC, CA);
    //            DirectX::XMVECTOR Dot3 = DirectX::XMVector3Dot(Cross3, N);
    //            float dot3;
    //            DirectX::XMStoreFloat(&dot3, Dot3);
    //            if (dot3 < 0.0f)continue;

    //            //�ŋߋ������X�V
    //            neart = x;

    //            //��_�Ɩ@�����X�V
    //            HitPosition = P;
    //            HitNormal = N;
    //            materialIndex = subset.materialIndex;
    //        }
    //    }
    //    if (materialIndex >= 0)
    //    {
    //        //���[�J����Ԃ��烏�[���h��Ԃ֕ϊ�
    //        DirectX::XMVECTOR WorldPosition = DirectX::XMVector3TransformCoord(HitPosition, WorldTransform);
    //        DirectX::XMVECTOR WorldCrossVec = DirectX::XMVectorSubtract(WorldPosition, WorldStart);
    //        DirectX::XMVECTOR WorldCrossLength = DirectX::XMVector3Length(WorldCrossVec);
    //        float distance;
    //        DirectX::XMStoreFloat(&distance, WorldCrossLength);

    //        //�q�b�g���ۑ�
    //        if (result.distance > distance)
    //        {
    //            DirectX::XMVECTOR WorldNormal = DirectX::XMVector3TransformNormal(
    //                HitNormal,
    //                WorldTransform);

    //            result.distance = distance;
    //            result.materialIndex = materialIndex;
    //            DirectX::XMStoreFloat3(&result.position, WorldPosition);
    //            DirectX::XMStoreFloat3(&result.normal, DirectX::XMVector3Normalize(WorldNormal));
    //            hit = true;
    //        }
    //    }
    //}

    //return hit;
    //////�ȑO�̏����������������悤�ɉ��̎���
    ////if (end.y < 0.0f)
    ////{
    ////    result.position.x = end.x;
    ////    result.position.y = 0.0f;
    ////    result.position.z = end.z;
    ////    result.normal.x = 0.0f;
    ////    result.normal.y = 1.0f;
    ////    result.normal.z = 0.0f;
    ////    return true;
    ////}
       return false;
    //
}
