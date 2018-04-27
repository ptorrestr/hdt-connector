import numpy as np
from itertools import islice
from hdtconnector.libhdtconnector import HDTConnector
from hdtconnector.libhdtconnector import triple_role
import pytest

m_file = "etc/test.hdt"

def iterator_triple_id(m_map, type_):
    triples = np.array(
        [( triple.get_subject(),
            triple.get_object())
            for triple in m_map.search_id(0, 0, 0)]
        , dtype = type_)
    return 1

@pytest.mark.parametrize("type_", ["u4,u4","u8,u8"])
def test_iterator_triple_id_peformance(benchmark, type_):
    m_map = HDTConnector(m_file)
    result = benchmark(iterator_triple_id, m_map, type_)

def iterator_triple_string(m_map):
    triples = np.array(
        [( triple.get_subject(),
            triple.get_object())
            for triple in m_map.search("", "", "")]
        )
    return 1

def test_iterator_triple_string(benchmark):
    m_map = HDTConnector(m_file)
    result = benchmark(iterator_triple_string, m_map)
