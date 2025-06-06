#include "Collision.h"

namespace PhysicEngine {

	bool AABB(ManiFold& maniFold)
	{
		return false;
	}

	// -- SAT --
	bool SAT(ManiFold& maniFold)
	{
		Object& objA = *maniFold.ObjectA;
		Object& objB = *maniFold.ObjectB;
		float depth = std::numeric_limits<float>::max();
		Vector2f normal;

		std::vector<Vector2f> verticesA = objA.Collider.GetVertices();
		std::vector<Vector2f> verticesB = objB.Collider.GetVertices();

		for (std::size_t i = 0; i < verticesA.size(); i++) // Verifica collisione sugli assi del primo oggetto
		{
			float minA, maxA, minB, maxB;

			// Ottieni l'asse dell'oggetto A
			Vector2f axis = GetAxis(verticesA[i], verticesA[(i + 1) % verticesA.size()]);

			// Proietta i punti sugli assi
			projectPoint(axis, verticesA, minA, maxA);
			projectPoint(axis, verticesB, minB, maxB);

			// Se non c'è sovrapposizione su questo asse, non c'è collisione
			if (!(maxA > minB && maxB > minA))
			{
				maniFold = ManiFold(maniFold.ObjectA, maniFold.ObjectB);
				return false;
			}

			// Calcola la sovrapposizione su questo asse
			float overlap = std::min(maxA, maxB) - std::max(minA, minB);

			// Se la sovrapposizione è più piccola di quella già trovata, aggiorna
			if (overlap < depth) {
				depth = overlap;
				normal = axis;
			}
		}

		for (std::size_t i = 0; i < verticesB.size(); i++) // Verifica collisione sugli assi del secondo oggetto
		{
			float minA, maxA, minB, maxB;

			// Ottieni l'asse dell'oggetto B
			Vector2f axis = GetAxis(verticesB[i], verticesB[(i + 1) % verticesB.size()]);

			// Proietta i punti sugli assi
			projectPoint(axis, verticesA, minA, maxA);
			projectPoint(axis, verticesB, minB, maxB);

			// Se non c'è sovrapposizione su questo asse, non c'è collisione
			if (!(maxA > minB && maxB > minA))
			{
				maniFold = ManiFold(maniFold.ObjectA, maniFold.ObjectB);
				return false;
			}

			// Calcola la sovrapposizione su questo asse
			float overlap = std::min(maxA, maxB) - std::max(minA, minB);

			// Se la sovrapposizione è più piccola di quella già trovata, aggiorna
			if (overlap < depth) {
				depth = overlap;
				normal = axis;
			}	if (overlap < depth) {
				depth = overlap;
				normal = axis;
			}
		}

		Vector2f CenterA = ArithmeticMean(verticesA);
		Vector2f CenterB = ArithmeticMean(verticesB);
		Vector2f direction = CenterB - CenterA;

		if (DotProduct(normal, direction) < 0.f)
			normal = -normal;

		maniFold.Depth = depth;
		maniFold.Normal = normal;

		FindContactPoint(verticesA, verticesB, maniFold);

		return true; // Se tutte le collisioni sugli assi sono verificate, c'è collisione
	}
	void FindContactPoint(const std::vector<Vector2f>& verticesA, const std::vector<Vector2f>& verticesB, ManiFold& maniFold)
	{
		Vector2f contactA;
		Vector2f contactB;
		int count = 0;

		float minDistsq = std::numeric_limits<float>::max();

		for (std::size_t i = 0; i < verticesA.size(); i++)
		{
			Vector2f p = verticesA[i];

			for (std::size_t j = 0; j < verticesB.size(); j++)
			{
				Vector2f va = verticesB[j];
				Vector2f vb = verticesB[(j + 1) % verticesB.size()];

				float distsq = 0;
				Vector2f cp;
				PointSegmentDistance(p, va, vb, distsq, cp);

				if (NearlyEqual(distsq, minDistsq))
				{
					if (!NearlyEqual(cp, contactA))
					{
						contactB = cp;
						count = 2;
					}
				}
				else if (distsq < minDistsq)
				{
					minDistsq = distsq;
					contactA = cp;
					count = 1;
				}
			}
		}

		for (std::size_t i = 0; i < verticesB.size(); i++)
		{
			Vector2f p = verticesB[i];

			for (std::size_t j = 0; j < verticesA.size(); j++)
			{
				Vector2f va = verticesA[j];
				Vector2f vb = verticesA[(j + 1) % verticesA.size()];

				float distsq = 0;
				Vector2f cp;
				PointSegmentDistance(p, va, vb, distsq, cp);

				if (NearlyEqual(distsq, minDistsq))
				{
					if (!NearlyEqual(cp, contactA))
					{
						contactB = cp;
						count = 2;
					}
				}
				else if (distsq < minDistsq)
				{
					minDistsq = distsq;
					contactA = cp;
					count = 1;
				}
			}
		}

		maniFold.ContactPointA = contactA;
		maniFold.ContactPointB = contactB;
		maniFold.ContactCount = count;
	}
	const Vector2f& GetAxis(const Vector2f& axisA, const Vector2f& axisB)
	{
		return NormalizeVector(Vector2f(-(axisB.Y - axisA.Y), (axisB.X - axisA.X)));
	}
	void projectPoint(const Vector2f& axis, const std::vector<Vector2f>& vertices, float& min, float& max)
	{
		min = max = DotProduct(vertices[0], axis); // Imposta come valori per min max il primo vertice

		for (size_t i = 1; i < vertices.size(); i++)
		{
			float proiezione = DotProduct(vertices[i], axis);

			if (min > proiezione) min = proiezione; // Salva il valore se min é maggiore del vertice successivo
			if (max < proiezione) max = proiezione; // Salva il valore se max é minore del vertice successivo
		}
	}

}