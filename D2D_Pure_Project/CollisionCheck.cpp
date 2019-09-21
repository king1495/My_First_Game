#include "stdafx.h"
#include "InGameScene.h"

void InGameScene::CollisionCheck() {
	D2D1_ELLIPSE pCircle = pPlayer->GetCircle();
	vector<BulletClass*> pBullets = _BulletManager->GetBullets();
	vector<EnemyClass*> vEnemys = _EnemyManager->GetEnemys();
	vector<ItemClass*> vItem = pItem->GetItems();

	for (int i = 0; i < vEnemys.size(); ++i) {
		if (!vEnemys[i]->GetisActive()) continue;
		//	�÷��̾�� ���� �浹
		D2D1_ELLIPSE eCircle = vEnemys[i]->GetCircle();
		if (isCircleInCircle(eCircle, pCircle) && pPlayer->GetisActive() <= 0) {
			pPlayer->HitDamage();
			vEnemys[i]->HitDamage();
			if (vEnemys[i]->GetHp() <= 0)
			{
				vEnemys[i]->SetisActive();
			}
			pPlayer->SetisActive(60);
		}

		//	ź�� ���� �Ǵ� �÷��̾� �浹
		for (int j = 0; j < pBullets.size(); ++j) {
			if (!pBullets[j]->GetisActive()) continue;
			D2D1_ELLIPSE bCircle = pBullets[j]->GetCircle();

			switch (pBullets[j]->GetWhos()) {
			case 0:	//	�Ѿ��� ����
				if (isCircleInCircle(eCircle, bCircle)) {
					// ��ź�̰ų� ü���̸� �ȵ�
					pBullets[j]->HitDamage();
					for (int k = 0; k < _DB->GetAttack_Power(); ++k) vEnemys[i]->HitDamage();
					if (vEnemys[i]->GetHp() <= 0)
					{
						if (isBossOn && vEnemys[i]->GetType() == isBoss) {
							isWin = true;
							return;
						}

						if (GetRandomInt(0, 19) == 0) {
							pItem->ActiveItem(
								(tagItem)GetRandomInt(0, 2),
								eCircle.point
							);
						}
						vEnemys[i]->SetisActive();
						Score++;
					}
				}
				break;

			case 1:	//	�Ѿ��� ������
				if (isCircleInCircle(bCircle, pCircle)) {
					pBullets[j]->HitDamage();
					if (pPlayer->GetisActive() <= 0) {
						pPlayer->HitDamage();
						pPlayer->SetisActive(60);
					}
				}
				break;
			}
		}
	}

	for (int i = 0; i < vItem.size(); ++i) {
		if (!vItem[i]->GetisActive()) continue;
		D2D1_ELLIPSE iCircle = vItem[i]->GetCircle();
		if (isCircleInCircle(iCircle, pCircle)) {
			switch (vItem[i]->GetType())
			{
			case isHeal:
				pPlayer->AddHp();
				break;

			case isCoolTime:
				pPlayer->ResetCooltime();
				break;

			case isAttack:
				_DB->SetAttack_Power(_DB->GetAttack_Power());
				break;
			}
			vItem[i]->SetisActive();
		}
	}
}