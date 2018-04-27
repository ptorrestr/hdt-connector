import numpy as np
from itertools import islice
from hdtconnector.libhdtconnector import HDTConnector
from hdtconnector.libhdtconnector import triple_role
import pytest

m_file = "etc/test.hdt"

def iterator_triple_id(m_map, rounds):
    for i in range(rounds):
        triples = np.array(
            [ triple.get_subject()
                for triple in m_map.search_id(0, 0, 0)]
            ,dtype = "u4")
    return 1

@pytest.mark.parametrize("rounds", [10, 50, 100])
def test_iterator_triple_id_peformance(benchmark, rounds):
    m_map = HDTConnector(m_file)
    result = benchmark(iterator_triple_id, m_map, rounds)
