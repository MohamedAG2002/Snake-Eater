#pragma once

class Score
{
public:
	Score();
	~Score();

private:
	int m_score, m_highScore;

public:
	void SetScore(const int score) { m_score = score; }
	const int& GetScore() const { return m_score; }
	
	void SetHighScore(const int highScore) { m_highScore = highScore; }
	const int& GetHighScore() const { return m_highScore; }
};
extern Score score;