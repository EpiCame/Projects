#pragma once
#include "model.h"
#include "Repo.h"
class undo_action {
public:
	virtual void make_undo() = 0;
	
	virtual ~undo_action() = default;
};

class undo_add : public undo_action {
	Movie added_movie;
	Repository& repo;
public:
	undo_add(Repository& repo, const  Movie& mv) :repo{ repo }, added_movie{ mv } {}
	void make_undo() override {
		repo.erase(added_movie);
	}
};

class undo_erase : public undo_action {
	Movie erased_movie;
	Repository& repo;
public:
	undo_erase(Repository& repo, const  Movie& mv) :repo{ repo }, erased_movie{ mv } {}
	void make_undo() override {
		repo.add(erased_movie);
	}
};

class undo_modify : public undo_action {
	Movie modified_movie;
	Movie new_movie;
	Repository& repo;
public:
	undo_modify(Repository& repo, const  Movie& mv1, const  Movie& mv2) :repo{ repo }, modified_movie{ mv1 }, new_movie{ mv2 }{}
	void make_undo() override {
		repo.modify(new_movie, modified_movie);
	}
};


