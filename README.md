# Decision Tree

[![Build Status](https://travis-ci.org/juliangaal/DecisionTree.svg?branch=master)](https://travis-ci.org/juliangaal/DecisionTree) 

Decision Tree implementation in C++ based on Gini uncertainty and [this](https://github.com/random-forests/tutorials/blob/master/decision_tree.py) great example.

## Graphviz File Generator
use built-in [Graphviz](https://www.graphviz.org) dot file generator to export decision tree to `.dot` file, that you can visualize with [xdot](https://github.com/jrfonseca/xdot.py) or an online viewer. Example graph:

<p align="center">
    <img alt="Alt Text" src="docs/iris.dot.jpg?raw=true" />
</p>

results from [iris.dot](docs/graph.dot) and [this](test/data/iris.csv) dataset.

## Requirements
* Boost (algorithm header)
* {fmt}
* gcc >= 8
* cmake >= 3.9
* Catch (for testing)

## TODO
* handle missing data in files
* pruning? 
* `std::filesystem`
