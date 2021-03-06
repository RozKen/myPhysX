#include "ActorGroundPlane.h"

void ActorGroundPlane::Create(){

	NxActorDesc	actorDesc;			///actor Descriptor with Collection of Shapes.
	NxPlaneShapeDesc	planeDesc;	///Plane Shape Descriptor
	
	//平面方程式: ax + by + cz + d = 0;
	planeDesc.normal = NxVec3(0, 1, 0);		//面の法線はY軸(↑)方向
	planeDesc.d = 0.0f;								//Y = 0.0fに面を作る

	actorDesc.shapes.pushBack( &planeDesc );	//ActorにPlaneを登録

	//NxScene Creates Actor and Returns a Pointer.
	_pActor = _pScene->createActor( actorDesc);
	_pActor->userData = NULL;		//PhysX上のActorと(ゲームなどの)データ上のActorを結びつける
		
	//Set the parameters for the Default Material
	//Physicsの"Material"とは目に見える表面材質ではなく，物体の物理学的特徴を表す
	NxMaterial* defaultMaterial = _pScene->getMaterialFromIndex( 0 );
	defaultMaterial->setRestitution( 0.3f );			//反発係数
	defaultMaterial->setStaticFriction( 0.5f );		//静止摩擦係数
	defaultMaterial->setDynamicFriction( 0.5f );	//動摩擦係数
}

void ActorGroundPlane::draw() const{
	glColor4f(0.0f, 0.8f, 0.0f, 1.0f);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		for(int i=-_numGridLine;i<=_numGridLine;i++) {
			//Lines Parallel to Z Axis
			glVertex3f(i*_scaleGridLine, (GLfloat)_yGround, -_numGridLine * _scaleGridLine);
			glVertex3f(i*_scaleGridLine, (GLfloat)_yGround, _numGridLine * _scaleGridLine);
			//Lines Prallel to X Axis
			glVertex3f(_numGridLine * _scaleGridLine, (GLfloat)_yGround, i*_scaleGridLine);
			glVertex3f(-_numGridLine * _scaleGridLine, (GLfloat)_yGround, i*_scaleGridLine);
		}
	glEnd();
	glEnable(GL_LIGHTING);
}