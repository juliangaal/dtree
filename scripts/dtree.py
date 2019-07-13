#!/usr/bin/env python3
import dtree_py as dt

dtree = dt.DecisionTree(dt.TrainingSet("../test/data/san_fran_vs_nyc.csv", dt.SkipDescription.NO, ","),
                        dt.TestingSet("../test/data/san_fran_vs_nyc_test.csv", ","))
dtree.build()
dtree.test()
dtree.generate_graph("../from_py.dot")


