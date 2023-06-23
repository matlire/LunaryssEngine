#include "Camera.h"

using namespace std;

Camera::Camera(Player& player, World& world, double radFov, int depth, int rayNum, int windowHeight, double projK, double sDist, int pScale, bool eyeC)
{
    this->player = player;
    this->radFov = radFov;
    this->depth = depth;
    this->rayNum = rayNum;
    this->world = world;
    this->windowHeight = windowHeight;
    this->projK = projK;
    this->sDist = sDist;
    this->pScale = pScale;
    this->eyeC = eyeC;
    oldFrame.direction = 0;
}

void Camera::StartFrameProcessing()
{
	
}

void Camera::EndFrameProcessing()
{
	swap(oldFrame, curFrame);
    if (this->direction < 0 + P_RSPEED) { this->direction = PI * 2 - 0.0001; }
    else if (this->direction >= PI * 2) { this->direction = 0 + 0.0001; }
	oldFrame.direction = this->direction;
    this->angle = Rad2Degree(direction);
    oldFrame.angle = this->angle;
	oldFrame.position = this->player.GetPos();
}

bool Camera::Input(double elapsedTime, sf::RenderWindow& window)
{
    this->map = false;
    if (!window.hasFocus())
    {
        this->hadFocus = false;
		return true;
    }

    double dx = 0;
    double dy = 0;
    double d_sin = sin(oldFrame.direction);
    double d_cos = cos(oldFrame.direction);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->direction -= this->player.GetRotateSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->direction += this->player.GetRotateSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        dx = d_cos;
        dy = d_sin;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        dx = -d_cos;
        dy = -d_sin;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
        this->map = true;
    }

    Shift({ dx * this->player.GetWalkSpeed() * elapsedTime, dy * this->player.GetWalkSpeed() * elapsedTime });

    this->hadFocus = true;
    return true;
}

bool Camera::OnSegment(Point2D p, Point2D q, Point2D r)
{
    if (q.GetVector().x <= max(p.GetVector().x, r.GetVector().x) && q.GetVector().x >= min(p.GetVector().x, r.GetVector().x) &&
        q.GetVector().y <= max(p.GetVector().y, r.GetVector().y) && q.GetVector().y >= min(p.GetVector().y, r.GetVector().y))
        return true;
    return false;
}

double Camera::Orientation(Point2D p, Point2D q, Point2D r)
{
    double val = (q.GetVector().y - p.GetVector().y) * (r.GetVector().x - q.GetVector().x) - (q.GetVector().x - p.GetVector().x) * (r.GetVector().y - q.GetVector().y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

bool Camera::DoIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2)
{
    int o1 = Orientation(p1, q1, p2);
    int o2 = Orientation(p1, q1, q2);
    int o3 = Orientation(p2, q2, p1);
    int o4 = Orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && OnSegment(p1, p2, q1)) return true;

    if (o2 == 0 && OnSegment(p1, q2, q1)) return true;

    if (o3 == 0 && OnSegment(p2, p1, q2)) return true;

    if (o4 == 0 && OnSegment(p2, q1, q2)) return true;

    return false;
}

void Camera::IntersectionPoint(Point2D p1, Point2D q1, Point2D p2, Point2D q2, Point2D& intersection)
{
    double a1 = q1.GetVector().y - p1.GetVector().y;
    double b1 = p1.GetVector().x - q1.GetVector().x;
    double c1 = a1 * p1.GetVector().x + b1 * p1.GetVector().y;

    double a2 = q2.GetVector().y - p2.GetVector().y;
    double b2 = p2.GetVector().x - q2.GetVector().x;
    double c2 = a2 * p2.GetVector().x + b2 * p2.GetVector().y;

    double det = a1 * b2 - a2 * b1;
    if (det == 0)
    {
        intersection.SetVector(sf::Vector2f(-1, -1));
    }
    else 
    {
        intersection.SetVector(sf::Vector2f((b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det));
    }
}

void Camera::Handle(sf::RenderTarget& window)
{       
    double newDir = oldFrame.direction - this->radFov / 2;
    
    vector<Ray> rays;
    for (int i = 0; i < this->rayNum; i++)
    {
        Ray ray = Ray(this->player.GetRealPos(), this->depth, newDir);

        for (auto j : this->world.GetMap())
        {
            vector<Point2D> pts = j.GetPoints2D();
            for (int k = 0; k < pts.size(); k++)
            {
                Point2D pFigLineStart = pts[k];
                Point2D pFigLineEnd;
                if (pts.size() > static_cast<unsigned long long>(k) + 1)
                {
                    pFigLineEnd = j.GetPoints2D()[static_cast<std::vector<Point2D, std::allocator<Point2D>>::size_type>(k) + 1];
                }
                else
                {
                    pFigLineEnd = j.GetPoints2D()[0];
                }
                Point2D rayStart = ray.GetStart();
                Point2D rayEnd = ray.GetEnd();

                Point2D intersection;
                if (DoIntersect(rayStart, rayEnd, pFigLineStart, pFigLineEnd)) {
                    IntersectionPoint(rayStart, rayEnd, pFigLineStart, pFigLineEnd, intersection);
                    ray.SetEnd(intersection);
                }
            }
        }
        
        double wallDist = (sqrt(pow(abs((ray.GetStart().GetVector().x - ray.GetEnd().GetVector().x)), 2) + pow(abs((ray.GetStart().GetVector().y - ray.GetEnd().GetVector().y)), 2)));
        if (this->eyeC) { wallDist *= cos(abs(direction - newDir)); }
        double projHeight = this->projK / wallDist;
        double c = 255 / (1 + wallDist * wallDist * 0.0001);
        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(this->pScale, projHeight));
        rect.setPosition(i*pScale, (this->windowHeight / 2) - projHeight / 2);
        rect.setFillColor(sf::Color(c, c, c));

        if (!this->map)
        {
            window.draw(rect);
        }

        rays.push_back(ray);
        newDir += this->radFov / rayNum;
    }
    if (this->map)
    {
        world.Draw(window);
        if (DEBUG)
        {
            for (auto& i : this->rays)
            {
                window.draw(i.GetLine());
            }
        }
        this->player.Draw(window);
    }
    this->rays = rays;
}

void Camera::Shift(Point2D vector)
{
    player.SetPos(player.GetPos() += vector);
}

double Camera::Degree2Rad(double degree)
{
    return degree * PI / 180;
}

double Camera::Rad2Degree(double rad)
{
    return rad * 180 / PI;
}